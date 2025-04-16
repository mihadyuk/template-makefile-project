#include <stdexcept>
#include <vector>
#include "lrucache.h"

/*
146. LRU Cache
Medium
Topics
Companies
Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return -1.
void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
The functions get and put must each run in O(1) average time complexity.



Example 1:

Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4


Constraints:

1 <= capacity <= 3000
0 <= key <= 104
0 <= value <= 105
At most 2 * 105 calls will be made to get and put.
*/
void LRUCache::create(int capacity) {
    capacity_ = capacity;
}

void LRUCache::put(int key, int value) {

    if (cache_.size() >= (size_t)capacity_) {
        int min = 32767;
        bool min_found = false;
        int found_key = 0;
        for (const auto &it : usage_) {
            if (it.second < min) {
                min_found = true;
                found_key = it.first;
                min = it.second;
            }
        }
        if (min_found) {
            cache_.erase(found_key);
            usage_.erase(found_key);
        }
        else
            throw std::invalid_argument("key not found");
    }

    if (usage_.contains(key) == false) {
        usage_[key] = 1;
    }
    else {
        usage_[key]++;
    }
    cache_[key] = value;
}

int LRUCache::get(int key) {

    if (usage_.contains(key)) {
        usage_[key]++;
    }
    if (cache_.contains(key))
        return cache_[key];
    return -1;
}

/*
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4
*/
void LRUCache::run() {
    std::vector<int> retval;

    create(2);

    put(1, 1);
    put(2, 2);
    retval.push_back(get(1));

    put(3, 3);
    retval.push_back(get(2));

    put(4, 4);
    retval.push_back(get(1));
    retval.push_back(get(3));
    retval.push_back(get(4));


}
