#pragma once

#include "map.cpp"
#include "pair.cpp"
//#include "../C++/functions/hash/hash_func.cpp"
#include "./linked_list.cpp"

template <class K, class V>
class open_hash_map : map<K, V>
{
private:
  // list<pair<K, V>>[]
  list<pair<K, V>> *arr;
  int arrSize;
  int count = 0;
  hash_func<K> *h;

  int abs(int x)
  {
    if (x < 0)
    {
      return -x;
    }

    return x;
  }

  int getPos(K key)
  {
    return abs(h->hash(key) % this->arrSize);
  }

public:
  open_hash_map(int expectedSize, hash_func<K> *h)
  {
    this->h = h;
    this->arrSize = 2 * expectedSize - 1;
    this->arr = new list<pair<K, V>>[this->arrSize];
    for (int i = 0; i < this->arrSize; i++)
    {
      arr[i] = nullptr;
    }
  }

  virtual void set(K key, V value) override
  {
    remove(key);

    int pos = getPos(key);

    if (this->arr[pos] == nullptr)
    {
      this->arr[pos] = new linked_list<pair<K, V>>();
    }

    list<pair<K, V>> *bucket = this->arr[pos];
    bucket->insert(pair<K, V>(key, value));
    this->count++;
  }

  virtual V get(K key) override {
    
  }

  virtual bool contains(K key) override
  {
    int pos = getPos(key);

    if (this->arr[pos] == nullptr)
    {
      return false;
    }

    list<pair<K, V>> *l = this->arr[pos];
    return l->contains(pair<K, V>(key));
  }

  virtual void remove(K key) override {

  }

  virtual int size() override
  {
    return this->count;
  }
};