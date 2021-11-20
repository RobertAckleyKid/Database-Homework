/**
 * LRU implementation
 */
#include "buffer/lru_replacer.h"
#include "page/page.h"

namespace scudb {

    template <typename T> LRUReplacer<T>::LRUReplacer() : numNode(0) 
    {
        head = new BiNode();
        tail = head;
    }

    template <typename T> LRUReplacer<T>::~LRUReplacer() = default;

/*
 * Insert value into LRU
 */
    template <typename T> void LRUReplacer<T>::Insert(const T &value) 
    {
        std::lock_guard<std::mutex> lock(mutex_w);
        
        auto target = tables.find(value);
        if (target == tables.end()) 
        {
            tail->nextNode = new BiNode(value, tail);
            tail = tail->nextNode;
            tables.emplace(value, tail);
            numNode++;
        }
        else 
        {
            if (target->second != tail) 
            {
                BiNode* preNode = target->second->preNode;
                BiNode* curNode = preNode->nextNode;
                preNode->nextNode = std::move(curNode->nextNode);
                preNode->nextNode->preNode = preNode;

                curNode->preNode = tail;
                tail->nextNode = std::move(curNode);
                tail = tail->nextNode;
            }
        }
    }

/* If LRU is non-empty, pop the head member from LRU to argument "value", and
 * return true. If LRU is empty, return false
 */
    template <typename T> bool LRUReplacer<T>::Victim(T& value) 
    {
        std::lock_guard<std::mutex> lock(mutex_w);
        if (numNode == 0) {
            return false;
        }
        value = head->nextNode->value;
        head->nextNode = head->nextNode->nextNode;
        if (head->nextNode != nullptr) {
            head->nextNode->preNode = head;
        }

        tables.erase(value);
        if (--numNode == 0) {
            tail = head;
        }

        return true;
    }

/*
 * Remove value from LRU. If removal is successful, return true, otherwise
 * return false
 */
    template <typename T> bool LRUReplacer<T>::Erase(const T& value) 
    {
        std::lock_guard<std::mutex> lock(mutex_w);
        auto target = tables.find(value);
        if (target != tables.end()) {
            if (target->second != tail) {
                BiNode* preNode = target->second->preNode;
                BiNode* curNode = preNode->nextNode;
                preNode->nextNode = std::move(curNode->nextNode);
                preNode->nextNode->preNode = preNode;
            }
            else {
                tail = tail->preNode;
                delete tail->nextNode;
            }
            tables.erase(value);
            if (--numNode == 0) {
                tail = head;
            }
            return true;
        }

        return false;
    }

    template <typename T> size_t LRUReplacer<T>::Size() 
    {
        std::lock_guard<std::mutex> lock(mutex_w);
        return numNode;
    }

template class LRUReplacer<Page *>;
// test only
template class LRUReplacer<int>;

} // namespace scudb