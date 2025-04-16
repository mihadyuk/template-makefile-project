#ifndef LRUCACHE_H
#define LRUCACHE_H
#include <unordered_map>

class LRUCache
{
public:
    void run();
private:
    void create(int capacity);
    void put(int key, int value);
    int get(int key);

    std::unordered_map<int, int> cache_;
    std::unordered_map<int, int> usage_;
    int capacity_ = 0;
};

#endif // LRUCACHE_H
