#include "Map.hpp"
#include "JSONValue.hpp"

template <typename K, typename V>
Map<K, V>::Map()
{
    this->entries = new Entry<K, V>[0];
    this->size = 0;
}

template <typename K, typename V>
Map<K, V>::Map(const Map &other)
{
    this->entries = new Entry<K, V>[other.size];
    this->size = other.size;

    for (int i = 0; i < this->size; i++)
    {
        this->entries[i] = other.entries[i];
    }
}

template <typename K, typename V>
Map<K, V> &Map<K, V>::operator=(const Map &other)
{
    delete[] this->entries;
    this->entries = new Entry<K, V>[other.size];
    this->size = other.size;

    for (int i = 0; i < this->size; i++)
    {
        this->entries[i] = other.entries[i];
    }

    return *this;
}

template <typename K, typename V>
V Map<K, V>::get(K key)
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->entries[i].key == key)
        {
            return this->entries[i].value;
        }
    }

    // throw "Error in Map::get: Key not found";
}

template <typename K, typename V>
void Map<K, V>::put(K key, V value)
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->entries[i].key == key)
        {
            this->entries[i].value = value;
            return;
        }
    }

    Entry<K, V> *newEntries = new Entry<K, V>[this->size + 1];

    for (int i = 0; i < this->size; i++)
    {
        newEntries[i] = this->entries[i];
    }

    newEntries[this->size].key = key;
    newEntries[this->size].value = value;

    delete[] this->entries;
    this->entries = newEntries;
    this->size++;
}

template <typename K, typename V>
void Map<K, V>::remove(K key)
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->entries[i].key == key)
        {
            Entry<K, V> *newEntries = new Entry<K, V>[this->size - 1];

            for (int j = 0; j < i; j++)
            {
                newEntries[j] = this->entries[j];
            }

            for (int j = i + 1; j < this->size; j++)
            {
                newEntries[j - 1] = this->entries[j];
            }

            delete[] this->entries;
            this->entries = newEntries;
            this->size--;

            return;
        }
    }

    // throw "Error in Map::remove: Key not found";
}

template <typename K, typename V>
int Map<K, V>::getSize()
{
    return this->size;
}

template <typename K, typename V>
bool Map<K, V>::operator==(const Map &other) const
{
    if (this->size != other.size)
    {
        return false;
    }

    for (int i = 0; i < this->size; i++)
    {
        if (!(this->entries[i].key == other.entries[i].key) || !(this->entries[i].value == other.entries[i].value))
        {
            return false;
        }
    }

    return true;
}

template <typename K, typename V>
Map<K, V>::~Map()
{
    delete[] this->entries;
}

template class Map<int, int>;
template class Map<JFA::String, JFA::String>;
template class Map<JFA::String, JSONValue>;