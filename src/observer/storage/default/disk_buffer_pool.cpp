/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Longda on 2021/4/13.
//
#include "disk_buffer_pool.h"
#include <errno.h>
#include <string.h>

#include "common/log/log.h"

using namespace common;

unsigned long current_time()
{
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC, &tp);
  return tp.tv_sec * 1000 * 1000 * 1000UL + tp.tv_nsec;
}

DiskBufferPool *theGlobalDiskBufferPool()
{
  static DiskBufferPool *instance = new DiskBufferPool();

  return instance;
}

RC DiskBufferPool::create_file(const char *file_name)
{
    /* O_RDWR 以可读可写的方式打开，
     * O_CREAT 如果文件不存在则创建一个新的文件
     * O_EXCL 如果文件已存在则返回一个错误
     *
     * S_ 设置读写性
     * S_IREAD 允许读
     * S_IWRITE 允许写
     */
  int fd = open(file_name, O_RDWR | O_CREAT | O_EXCL, S_IREAD | S_IWRITE);
  if (fd < 0) {
    LOG_ERROR("Failed to create %s, due to %s.", file_name, strerror(errno));
    return RC::SCHEMA_DB_EXIST;
  }
  close(fd);

  /**
   * Here don't care about the failure
   */
   // 为什么要先创建，关闭之后再重新open呢
  fd = open(file_name, O_RDWR);
  if (fd < 0) {
    LOG_ERROR("Failed to open for readwrite %s, due to %s.", file_name, strerror(errno));
    return RC::IOERR_ACCESS;
  }

  Page page;
  memset(&page, 0, sizeof(Page)); // void *memset(void *s, int ch, size_t n);
  // 将开始写入page的位置定位到最前面

  BPFileSubHeader *fileSubHeader;
  fileSubHeader = (BPFileSubHeader *)page.data; //进行强制类型转换：
  // 为什么一定要进行强制类型转换来实现？这样固定了这个新创建的文件的第一个page，通过这样的方法使得在第一个page的一开始记录这个文件的一些信息
  fileSubHeader->allocated_pages = 1;
  fileSubHeader->page_count = 1;

  char *bitmap = page.data + (int)BP_FILE_SUB_HDR_SIZE; //将之前记录了fileSubHeader信息的部分加上
  bitmap[0] |= 0x01; // bitmap[0]用于标识这个file的第一个page已经创建
  //?为什么这里要用或，如果是已经创建过一个同名文件不应该之前在一开始创建文件时就发生错误（因为open函数标志位O_EXCL）直接返回吗？
  // lseek函数，移动文件的读写位置 off_t lseek(int fildes, off_t offset, int whence);
  if (lseek(fd, 0, SEEK_SET) == -1) {
    LOG_ERROR("Failed to seek file %s to position 0, due to %s .", file_name, strerror(errno));
    close(fd);
    return RC::IOERR_SEEK;
  }
  // ssize_t write(int filedes, const void *buf, size_t nbytes); buf为写入的内容，nbytes为写入的长度
  // 这里写page的内容是吧BPFileSubHeader中的内容写入文件，相当于落盘,
  // 这里也会将page_num 写入磁盘，所以之后load_data的page_num是读出来的，
  // page_num 被默认初始化为0，所以不需要再特别的初始化page_num，所以直接写入磁盘即可
  if (write(fd, (char *)&page, sizeof(Page)) != sizeof(Page)) {
    LOG_ERROR("Failed to write header to file %s, due to %s.", file_name, strerror(errno));
    close(fd);
    return RC::IOERR_WRITE;
  }
  int a=page.page_num;
  std::cout<<fd<<std::endl;
  close(fd);
  LOG_INFO("Successfully create %s.", file_name);
  return RC::SUCCESS;
}

RC DiskBufferPool::open_file(const char *file_name, int *file_id)
{
  int fd, i;
  // This part isn't gentle, the better method is using LRU queue.
  // 检查这个文件是否已经被打开
  for (i = 0; i < MAX_OPEN_FILE; i++) {
    if (open_list_[i]) {
      if (!strcmp(open_list_[i]->file_name, file_name)) {
        *file_id = i;
        LOG_INFO("%s has already been opened.", file_name);
        return RC::SUCCESS;
      }
    }
  }
  i = 0;
  while (i < MAX_OPEN_FILE && open_list_[i++])// 找到open_list_的最末端 i++先赋值，再加1
    ;

  // open_list_[i] 取出来的每个打开文件的BPFileHandle 并不是bool值
  // 但是因为在进行或与非时，不是0都认为是1，所以如果open_list_[i]不为0说明有文件打开
  // 如果已经到了数组末尾并且最后一位也有已经打开的文件，说明打开的文件太多了

  // 为什么要进行这样的检验呢？如果open_list_最后一位为空的话，应该在MAX_OPEN_FILE-1就退出，通过i++最终为MAX_OPEN_FILE
  // 如果open_list_全满的时候，while循环应该在最后MAX_OPEN_FILE时退出，所以最终i为MAX_OPEN_FILE+1
  // 所以为什么不直接检验i？=MAX_OPEN_FILE+1呢  (可能是认为如果最终只剩了一个文件的位置，也认为已经打开了很多文件？)
  if (i >= MAX_OPEN_FILE && open_list_[i - 1]) {
    LOG_ERROR("Failed to open file %s, because too much files has been opened.", file_name);
    return RC::BUFFERPOOL_OPEN_TOO_MANY_FILES;
  }

  if ((fd = open(file_name, O_RDWR)) < 0) {
    LOG_ERROR("Failed to open file %s, because %s.", file_name, strerror(errno));
    return RC::IOERR_ACCESS;
  }
  LOG_INFO("Successfully open file %s.", file_name);

  // 通过BPFileHandle打开文件
  BPFileHandle *file_handle = new (std::nothrow) BPFileHandle();
  if (file_handle == nullptr) {
    LOG_ERROR("Failed to alloc memory of BPFileHandle for %s.", file_name);
    close(fd);
    return RC::NOMEM;
  }

  RC tmp;
  file_handle->bopen = true;
  int file_name_len = strlen(file_name) + 1;
  char *cloned_file_name = new char[file_name_len];
  snprintf(cloned_file_name, file_name_len, "%s", file_name);
  cloned_file_name[file_name_len - 1] = '\0';
  file_handle->file_name = cloned_file_name;
  file_handle->file_desc = fd;

  // 为文件分配好在内存中frame的位置
  if ((tmp = allocate_block(&file_handle->hdr_frame)) != RC::SUCCESS) {
      // 创建了file_handle 这个BPFileHandle 时就为其中hdr_frame成员变量有了空间，allocate应该是要将头部进行对应
    LOG_ERROR("Failed to allocate block for %s's BPFileHandle.", file_name);
    delete file_handle;
    close(fd);
    return tmp;
  }
  file_handle->hdr_frame->dirty = false;
  file_handle->hdr_frame->acc_time = current_time();
  file_handle->hdr_frame->file_desc = fd;
  file_handle->hdr_frame->pin_count = 1;

  // 如果将文件加载到内存中的frame出现问题
  if ((tmp = load_page(0, file_handle, file_handle->hdr_frame)) != RC::SUCCESS) {
    file_handle->hdr_frame->pin_count = 0;
    dispose_block(file_handle->hdr_frame);
    close(fd);
    delete file_handle;
    return tmp;
  }

  file_handle->hdr_page = &(file_handle->hdr_frame->page);
  file_handle->bitmap = file_handle->hdr_page->data + BP_FILE_SUB_HDR_SIZE;
  file_handle->file_sub_header = (BPFileSubHeader *)file_handle->hdr_page->data;
  open_list_[i - 1] = file_handle;
  *file_id = i - 1;
  LOG_INFO("Successfully open %s. file_id=%d, hdr_frame=%p", file_name, *file_id, file_handle->hdr_frame);
  return RC::SUCCESS;
}

RC DiskBufferPool::close_file(int file_id)
{
  RC tmp;
  if ((tmp = check_file_id(file_id)) != RC::SUCCESS) {
    LOG_ERROR("Failed to close file, due to invalid fileId %d", file_id);
    return tmp;
  }

  BPFileHandle *file_handle = open_list_[file_id];
  // 因为将所有打开文件的header frame都放在了内存中，即在open_file函数中将header Frame pin住了，
  // 所以需要将header Frame的pin_count-- ；从而可以释放这个文件在内存中占用的所有内存，否则header_Frame还会占用内存
  file_handle->hdr_frame->pin_count--;
  // 这里应该是释放所有这个文件在内存中的frame
  if ((tmp = force_all_pages(file_handle)) != RC::SUCCESS) {
    file_handle->hdr_frame->pin_count++;
    LOG_ERROR("Failed to closeFile %d:%s, due to failed to force all pages.", file_id, file_handle->file_name);
    return tmp;
  }

  if (close(file_handle->file_desc) < 0) {
    LOG_ERROR("Failed to close fileId:%d, fileName:%s, error:%s", file_id, file_handle->file_name, strerror(errno));
    return RC::IOERR_CLOSE;
  }

  // 这里open_list_对应位置必须设置为nullptr
  // 是因为在打开文件时是将open_list_遍历，找到最后一位在后面继续添加。
  // 不能向BPManger中的Frame按照allocated是否为空直接覆盖，所以必须将他重置为nullptr
  open_list_[file_id] = nullptr;
  delete (file_handle);
  LOG_INFO("Successfully close file %d:%s.", file_id, file_handle->file_name);
  return RC::SUCCESS;
}

RC DiskBufferPool::delete_file(const char *file_name){
  //先查找open_list,判断有没有打开，若没有打开，直接删除，若打开过，则需要close file再删除
    int fd, i, file_id;
    int rc = RC::SUCCESS;
  // This part isn't gentle, the better method is using LRU queue.
  for (i = 0; i < MAX_OPEN_FILE; i++) {
    if (open_list_[i]) {
      if (!strcmp(open_list_[i]->file_name, file_name)) {
        file_id = i;
        rc = close_file(file_id);
        break;
      }
    }
  }
  if(RC::SUCCESS != rc) {
    LOG_ERROR("Failed to delete file %d:%s due to close error.", file_id, file_name);
    return RC::IOERR_DELETE;
  }
  //删除文件
  if(remove(file_name)){
    LOG_ERROR("Failed to delete file %d:%s", file_id, file_name);
    return RC::IOERR_DELETE;
  }
  LOG_INFO("SUCCESS to delete file %d:%s", file_id, file_name);
  return RC::SUCCESS;
}

RC DiskBufferPool::get_this_page(int file_id, PageNum page_num, BPPageHandle *page_handle)
{
    // file_id就是在disk_buffer_pool中open_list_记录的这个文件的index

    // 检查所要取的文件file_id和所要取的页page_num是否存在
  RC tmp;
  if ((tmp = check_file_id(file_id)) != RC::SUCCESS) {
    LOG_ERROR("Failed to load page %d, due to invalid fileId %d", page_num, file_id);
    return tmp;
  }

  BPFileHandle *file_handle = open_list_[file_id];
  if ((tmp = check_page_num(page_num, file_handle)) != RC::SUCCESS) {
    LOG_ERROR("Failed to load page %s:%d, due to invalid pageNum.", file_handle->file_name, page_num);
    return tmp;
  }


  // 如果这个page已经加载到内存了了，找到打开的frame，记录在page_handle中

//找到分配过的frame且为对应文件的页面，若该页面的page_num正好为要找的page_num(已经被load进来)，初始化page_handle

  for (int i = 0; i < BP_BUFFER_SIZE; i++) {
    if (!bp_manager_.allocated[i])
      continue;
    if (bp_manager_.frame[i].file_desc != file_handle->file_desc)
      continue;

    // This page has been loaded.
    if (bp_manager_.frame[i].page.page_num == page_num) {
      page_handle->frame = bp_manager_.frame + i;
      page_handle->frame->pin_count++;
      page_handle->frame->acc_time = current_time();
      page_handle->open = true;
      return RC::SUCCESS;
    }
  }


  // 如果这个page没有被加载到内存，就将其加载到内存（allocate_block+load_page)
//走到这里说明没找到（没有load进来），分配一个额外的块，同样初始化page_handle元信息,然后把页面load进来

  // Allocate one page and load the data into this page
  if ((tmp = allocate_block(&(page_handle->frame))) != RC::SUCCESS) {
    LOG_ERROR("Failed to load page %s:%d, due to failed to alloc page.", file_handle->file_name, page_num);
    return tmp;
  }
  page_handle->frame->dirty = false;
  page_handle->frame->file_desc = file_handle->file_desc;
  page_handle->frame->pin_count = 1;
  page_handle->frame->acc_time = current_time();
  if ((tmp = load_page(page_num, file_handle, page_handle->frame)) != RC::SUCCESS) {
    LOG_ERROR("Failed to load page %s:%d", file_handle->file_name, page_num);
    page_handle->frame->pin_count = 0;
    dispose_block(page_handle->frame);
    return tmp;
  }

  page_handle->open = true;
  return RC::SUCCESS;
}

/**
* 在指定文件中分配一个新的页面，并将其放入缓冲区，返回页面句柄指针。
* 分配页面时，如果文件中有空闲页，就直接分配一个空闲页；
* 如果文件中没有空闲页，则扩展文件规模来增加新的空闲页。
*/
RC DiskBufferPool::allocate_page(int file_id, BPPageHandle *page_handle)
{
  RC tmp;
  if ((tmp = check_file_id(file_id)) != RC::SUCCESS) {
    LOG_ERROR("Failed to alloc page, due to invalid fileId %d", file_id);
    return tmp;
  }

  BPFileHandle *file_handle = open_list_[file_id];

  // 如果当前还有空闲页，就直接用这个空闲页
  int byte = 0, bit = 0;
  if ((file_handle->file_sub_header->allocated_pages) < (file_handle->file_sub_header->page_count)) {
    // There is one free page
    for (int i = 0; i < file_handle->file_sub_header->page_count; i++) {
        // 为什么这里要用byte 和bit
      byte = i / 8;
      bit = i % 8;
      if (((file_handle->bitmap[byte]) & (1 << bit)) == 0) {
        (file_handle->file_sub_header->allocated_pages)++;
        file_handle->bitmap[byte] |= (1 << bit);
        return get_this_page(file_id, i, page_handle);
      }
    }
  }

  if ((tmp = allocate_block(&(page_handle->frame))) != RC::SUCCESS) {
    LOG_ERROR("Failed to allocate page %s, due to no free page.", file_handle->file_name);
    return tmp;
  }

  PageNum page_num = file_handle->file_sub_header->page_count;
  file_handle->file_sub_header->allocated_pages++;
  file_handle->file_sub_header->page_count++;

  byte = page_num / 8;
  bit = page_num % 8;
  file_handle->bitmap[byte] |= (1 << bit);
  file_handle->hdr_frame->dirty = true;

  page_handle->frame->dirty = false;
  page_handle->frame->file_desc = file_handle->file_desc;
  page_handle->frame->pin_count = 1;
  page_handle->frame->acc_time = current_time();
  memset(&(page_handle->frame->page), 0, sizeof(Page));
  page_handle->frame->page.page_num = file_handle->file_sub_header->page_count - 1;

  // Use flush operation to extion file
  if ((tmp = flush_block(page_handle->frame)) != RC::SUCCESS) {
    LOG_ERROR("Failed to alloc page %s , due to failed to extend one page.", file_handle->file_name);
    return tmp;
  }

  page_handle->open = true;
  return RC::SUCCESS;
}

RC DiskBufferPool::get_page_num(BPPageHandle *page_handle, PageNum *page_num)
{
  if (!page_handle->open)
    return RC::BUFFERPOOL_CLOSED;
  *page_num = page_handle->frame->page.page_num;
  return RC::SUCCESS;
}

RC DiskBufferPool::get_data(BPPageHandle *page_handle, char **data)
{
  if (!page_handle->open)
    return RC::BUFFERPOOL_CLOSED;
  *data = page_handle->frame->page.data;
  return RC::SUCCESS;
}

RC DiskBufferPool::mark_dirty(BPPageHandle *page_handle)
{
  page_handle->frame->dirty = true;
  return RC::SUCCESS;
}

RC DiskBufferPool::unpin_page(BPPageHandle *page_handle)
{
  page_handle->open = false;
  page_handle->frame->pin_count--;
  return RC::SUCCESS;
}

/**
 * dispose_page will delete the data of the page of pageNum
 * force_page will flush the page of pageNum
 * @param fileID
 * @param pageNum
 * @return
 */
RC DiskBufferPool::dispose_page(int file_id, PageNum page_num)
{
  RC rc;
  if ((rc = check_file_id(file_id)) != RC::SUCCESS) {
    LOG_ERROR("Failed to alloc page, due to invalid fileId %d", file_id);
    return rc;
  }

  BPFileHandle *file_handle = open_list_[file_id];
  if ((rc = check_page_num(page_num, file_handle)) != RC::SUCCESS) {
    LOG_ERROR("Failed to dispose page %s:%d, due to invalid pageNum", file_handle->file_name, page_num);
    return rc;
  }

  for (int i = 0; i < BP_BUFFER_SIZE; i++) {
    if (!bp_manager_.allocated[i])
      continue;
    if (bp_manager_.frame[i].file_desc != file_handle->file_desc) {
      continue;
    }

    if (bp_manager_.frame[i].page.page_num == page_num) {
      if (bp_manager_.frame[i].pin_count != 0)
        return RC::BUFFERPOOL_PAGE_PINNED;
      bp_manager_.allocated[i] = false;
    }
  }

  file_handle->hdr_frame->dirty = true;
  file_handle->file_sub_header->allocated_pages--;
  // file_handle->pFileSubHeader->pageCount--;
  // 不进行page_count--是因为这样之后如果再利用这个page，
  // 那么可以直接利用之前他载入内存的frame，直接重新为他allocate_block并且向其写入即可，
  // 不需要再构造Frame，
  char tmp = 1 << (page_num % 8);
  file_handle->bitmap[page_num / 8] &= ~tmp;
  return RC::SUCCESS;
}

RC DiskBufferPool::force_page(int file_id, PageNum page_num)
{
  RC rc;
  if ((rc = check_file_id(file_id)) != RC::SUCCESS) {
    LOG_ERROR("Failed to alloc page, due to invalid fileId %d", file_id);
    return rc;
  }
  BPFileHandle *file_handle = open_list_[file_id];
  return force_page(file_handle, page_num);
}
/**
 * dispose_page will delete the data of the page of pageNum
 * force_page will flush the page of pageNum
 * @param fileHandle
 * @param pageNum
 * @return
 */
RC DiskBufferPool::force_page(BPFileHandle *file_handle, PageNum page_num)
{
  int i;
  for (i = 0; i < BP_BUFFER_SIZE; i++) {
    if (!bp_manager_.allocated[i])
      continue;

    Frame *frame = &bp_manager_.frame[i];
    if (frame->file_desc != file_handle->file_desc)
      continue;
    if (frame->page.page_num != page_num && page_num != -1) {
      continue;
    }

    if (frame->pin_count != 0) {
      LOG_ERROR("Page :%s:%d has been pinned.", file_handle->file_name, page_num);
      return RC::BUFFERPOOL_PAGE_PINNED;
    }

    if (frame->dirty) {
      RC rc = RC::SUCCESS;
      if ((rc = flush_block(frame)) != RC::SUCCESS) {
        LOG_ERROR("Failed to flush page:%s:%d.", file_handle->file_name, page_num);
        return rc;
      }
    }
    bp_manager_.allocated[i] = false;
    return RC::SUCCESS;
  }
  return RC::SUCCESS;
}

RC DiskBufferPool::flush_all_pages(int file_id)
{
  RC rc = check_file_id(file_id);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to flush pages due to invalid file_id %d", file_id);
    return rc;
  }

  BPFileHandle *file_handle = open_list_[file_id];
  return force_all_pages(file_handle);
}


// 释放这个file_handle 对应file，当前他在内存中使用的所有frame
RC DiskBufferPool::force_all_pages(BPFileHandle *file_handle)
{
// 传入参数file_handle是为了获得每个打开文件特定的file_descripter，
// 利用这个file_descripter 找到在BPManager Frame中所有此file_descripter对应的frame释放
// 既然只是需要一个file_descripter，为什么不直接传入一个file_descripter 而是要传入一个file_handle呢？
// 因为还需要在日志记录报错信息中输出file_name，所以用一个file_handle更方便
  for (int i = 0; i < BP_BUFFER_SIZE; i++) {
    if (!bp_manager_.allocated[i])
      continue;

    if (bp_manager_.frame[i].file_desc != file_handle->file_desc)
      continue;

    if (bp_manager_.frame[i].dirty) {
      RC rc = flush_block(&bp_manager_.frame[i]);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to flush all pages' of %s.", file_handle->file_name);
        return rc;
      }
    }
    // 这里只需要将BPManager的allocated对应位置进行更新而不需要将BPManger的Frame对应位置进行更新
    // 是因为Frame只是指针数组，是可以继续被覆盖的。所以当allocated对应位置置为false，
    // 那么当有下一个Frame需要使用这个位置的时候可以直接写入将原来旧的内容覆盖，所以不需要 Frame[i]=nullptr;
    bp_manager_.allocated[i] = false;
  }
  return RC::SUCCESS;
}

/*
 * flush_block函数就是load_page函数的反面，
 * load_page是从文件往frame中读
 * flush_block就是将frame中的内容写入磁盘
 * */
RC DiskBufferPool::flush_block(Frame *frame)
{
  // The better way is use mmap the block into memory,
  // so it is easier to flush data to file.

  // 找到文件的写入位置
  // ? 这里page_num 为什么不用减1呢？原因是在create_file中默认初始化page_num是从0开始的，所以不用-1
  s64_t offset = ((s64_t)frame->page.page_num) * sizeof(Page);
  if (lseek(frame->file_desc, offset, SEEK_SET) == offset - 1) {
    LOG_ERROR("Failed to flush page %lld of %d due to failed to seek %s.", offset, frame->file_desc, strerror(errno));
    return RC::IOERR_SEEK;
  }

  if (write(frame->file_desc, &(frame->page), sizeof(Page)) != sizeof(Page)) {
    LOG_ERROR("Failed to flush page %lld of %d due to %s.", offset, frame->file_desc, strerror(errno));
    return RC::IOERR_WRITE;
  }
  frame->dirty = false;
  LOG_DEBUG("Flush block. file desc=%d, page num=%d", frame->file_desc, frame->page.page_num);

  return RC::SUCCESS;
}

RC DiskBufferPool::allocate_block(Frame **buffer)
{

  // There is one Frame which is free.
  // 这一段是如果当前buffer还没有满，那么找到一个空的frame就把它给'参数buffer'用
  // 将其allocated
  for (int i = 0; i < BP_BUFFER_SIZE; i++) {
    if (!bp_manager_.allocated[i]) {
      bp_manager_.allocated[i] = true;
      *buffer = bp_manager_.frame + i;  // *buffer:Frame*
      LOG_DEBUG("Allocate block frame=%p", bp_manager_.frame + i);
      return RC::SUCCESS;
    }
  }

  // 如果现在buffer已经满了，那么需要用LRU原则来找到一个frame来进行替换
  // 下面就是要找一个最早被加入到buffer中的frame，也就是这个frame的acc_time最小
  int min = 0;
  unsigned long mintime = 0;
  bool flag = false;
  for (int i = 0; i < BP_BUFFER_SIZE; i++) {
    if (bp_manager_.frame[i].pin_count != 0) // 如果一个frame的pin_count被赋值，说明不能动这个frame
      continue;
    if (!flag) { // 如果这是第一个没有被pin的frame，之前还没有更新过mintime；
        // 这里不用i=0来判断是因为可能i=0的frame被pin了
      flag = true;
      min = i;
      mintime = bp_manager_.frame[i].acc_time;
    }
    if (bp_manager_.frame[i].acc_time < mintime) {
      min = i;
      mintime = bp_manager_.frame[i].acc_time;
    }
  }
  if (!flag) {
    LOG_ERROR("All pages have been used and pinned.");
    return RC::NOMEM;
  }
//replace
  // 找到了用于替换的frame，将脏页刷盘
  if (bp_manager_.frame[min].dirty) {
    RC rc = flush_block(&(bp_manager_.frame[min]));
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to flush block of %d for %d.", min, bp_manager_.frame[min].file_desc);
      return rc;
    }
  }
  // 指针+int：加一个对应类型的长度 如char指针+1 就是加1字节；int指针+1就是加4字节
  *buffer = bp_manager_.frame + min;
  return RC::SUCCESS;
}

RC DiskBufferPool::dispose_block(Frame *buf)
{
  if (buf->pin_count != 0) {
    LOG_WARN("Begin to free page %d of %d, but it's pinned.", buf->page.page_num, buf->file_desc);
    return RC::LOCKED_UNLOCK;
  }
  if (buf->dirty) {
    RC rc = flush_block(buf);
    if (rc != RC::SUCCESS) {
      LOG_WARN("Failed to flush block %d of %d during dispose block.", buf->page.page_num, buf->file_desc);
      return rc;
    }
  }
  buf->dirty = false;
  int pos = buf - bp_manager_.frame;
  bp_manager_.allocated[pos] = false;
  LOG_DEBUG("dispost block frame =%p", buf);
  return RC::SUCCESS;
}

RC DiskBufferPool::check_file_id(int file_id)
{
  if (file_id < 0 || file_id >= MAX_OPEN_FILE) {
    LOG_ERROR("Invalid fileId:%d.", file_id);
    return RC::BUFFERPOOL_ILLEGAL_FILE_ID;
  }
  if (!open_list_[file_id]) {
    LOG_ERROR("Invalid fileId:%d, it is empty.", file_id);
    return RC::BUFFERPOOL_ILLEGAL_FILE_ID;
  }
  return RC::SUCCESS;
}

RC DiskBufferPool::get_page_count(int file_id, int *page_count)
{
  RC rc = RC::SUCCESS;
  if ((rc = check_file_id(file_id)) != RC::SUCCESS) {
    return rc;
  }
  *page_count = open_list_[file_id]->file_sub_header->page_count;
  return RC::SUCCESS;
}

RC DiskBufferPool::check_page_num(PageNum page_num, BPFileHandle *file_handle)
{
  if (page_num >= file_handle->file_sub_header->page_count) {
    LOG_ERROR("Invalid pageNum:%d, file's name:%s", page_num, file_handle->file_name);
    return RC::BUFFERPOOL_INVALID_PAGE_NUM;
  }
  if ((file_handle->bitmap[page_num / 8] & (1 << (page_num % 8))) == 0) {
    LOG_ERROR("Invalid pageNum:%d, file's name:%s", page_num, file_handle->file_name);
    return RC::BUFFERPOOL_INVALID_PAGE_NUM;
  }
  return RC::SUCCESS;
}

RC DiskBufferPool::load_page(PageNum page_num, BPFileHandle *file_handle, Frame *frame)
{
  s64_t offset = ((s64_t)page_num) * sizeof(Page);
  if (lseek(file_handle->file_desc, offset, SEEK_SET) == -1) {
    LOG_ERROR(
        "Failed to load page %s:%d, due to failed to lseek:%s.", file_handle->file_name, page_num, strerror(errno));

    return RC::IOERR_SEEK;
  }
  // ssize_t read(int filedes, void *buf, size_t nbytes);
  // 从file_desc开始读sizeof(Page)的大小，读入&(frame->page);
  // 因为page_num在创建文件时也写入了，所以在load的时候直接读出来，就包括了page_num和page.data
  if (read(file_handle->file_desc, &(frame->page), sizeof(Page)) != sizeof(Page)) {
    LOG_ERROR(
        "Failed to load page %s:%d, due to failed to read data:%s.", file_handle->file_name, page_num, strerror(errno));
    return RC::IOERR_READ;
  }
  return RC::SUCCESS;
}
