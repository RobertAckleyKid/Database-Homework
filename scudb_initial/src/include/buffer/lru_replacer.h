/**
 * lru_replacer.h
 *
 * Functionality: The buffer pool manager must maintain a LRU list to collect
 * all the pages that are unpinned and ready to be swapped. The simplest way to
 * implement LRU is a FIFO queue, but remember to dequeue or enqueue pages when
 * a page changes from unpinned to pinned, or vice-versa.
 */

#pragma once

#include "buffer/replacer.h"
#include "hash/extendible_hash.h"

#include <map>
#include <mutex>
#include <memory>

namespace scudb {

template <typename T> class LRUReplacer : public Replacer<T> {
public:
  // do not change public interface
  LRUReplacer();

  ~LRUReplacer();

  void Insert(const T &value);

  bool Victim(T &value);

  bool Erase(const T &value);

  size_t Size();

private:
  // add your member variables here
  struct BiNode
  {
    T value;
    BiNode* preNode = nullptr;
    BiNode* nextNode = nullptr;
    BiNode() = default;
    explicit BiNode(T val, BiNode* node=nullptr)
    {
      value = val;
      preNode = node;
    }
  };
  std::map<T, BiNode*> tables;
  BiNode* head;
  BiNode* tail;
  mutable std::mutex mutex_w;
  size_t numNode;
};

} // namespace scudb
