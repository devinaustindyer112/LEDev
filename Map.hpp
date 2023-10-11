#ifndef MAP_HPP
#define MAP_HPP
#include "String.hpp"

template <typename K, typename V>
struct Entry
{
    K key;
    V value;
};

template <typename K, typename V>
class Map
{
private:
    Entry<K, V> *entries;
    int size;

public:
    Map();
    Map(const Map &other);
    Map &operator=(const Map &other);
    V get(K key);
    void put(K key, V value);
    void remove(K key);
    bool contains(K key);
    int getSize();
    bool operator==(const Map &map) const;
    ~Map();
};

#endif // MAP_HPP