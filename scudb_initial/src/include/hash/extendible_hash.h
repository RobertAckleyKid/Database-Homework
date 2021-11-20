/*
 * extendible_hash.h : implementation of in-memory hash table using extendible
 * hashing
 *
 * Functionality: The buffer pool manager must maintain a page table to be able
 * to quickly map a PageId to its corresponding memory location; or alternately
 * report that the PageId does not match any currently-buffered page.
 */

#pragma once

#include <vector>
#include <map>
#include <memory>
#include <mutex>
#include <cstdlib>
#include <string>

#include "hash/hash_table.h"

namespace scudb {

// My Bkt
//*********************************************//
template <typename K, typename V>
class Bucket
{
    int BktDepth;
    std::map<K,V> KVs;

    public:
      Bucket(int depth)
      {
        BktDepth = depth;
      }
      int GetBktDepth()
      {
        return BktDepth;
      }
      std::map<K,V> GetKVs()
      {
        return KVs;
      }
      bool KVfind(const K &key, V &value)
      {
        if(KVs.count(key))
        {
          value = KVs[key];
          return true;
        }
        return false;
      }
      bool KremoveKV(const K &key)
      {
        if(KVs.count(key))
        {
          KVs.erase(key);
          return true;
        }
        return false;
      }
      size_t GetKVsSize()
      {
        return KVs.size();
      }
      void insertKV(const K &key, const V &value)
      {
        if(KVs.count(key))
          return;
        KVs[key] = value;
      }
};
//*********************************************//
// My Bkt END!

template <typename K, typename V>
class ExtendibleHash : public HashTable<K, V> {
public:
  // constructor
  ExtendibleHash(size_t size);
  // helper function to generate hash addressing
  size_t HashKey(const K &key);
  // helper function to get global & local depth
  int GetGlobalDepth() const;
  int GetLocalDepth(int bucket_id) const;
  int GetNumBuckets() const;
  // lookup and modifier
  bool Find(const K &key, V &value) override;
  bool Remove(const K &key) override;
  void Insert(const K &key, const V &value) override;

private:
  // add your own member variables here
  int GetTableIndex(const K &key)
  {
    return HashKey(key) & ((1 << this->GlobalDepth) - 1);
  }
  int GlobalDepth;
  size_t BucketSize;
  int NumBuckets;
  std::vector<std::shared_ptr<Bucket<K,V>>> BucketTable;
  std::mutex mutex;
};
} // namespace scudb
