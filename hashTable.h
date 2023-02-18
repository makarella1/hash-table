#include "jedi.h"
#include "hashNode.h"

template <typename Key>
struct HashTable
{
  HashNode<Key> **buckets;
  int size;
  int capacity;
  double loadFactor;

  HashTable(int capacity = 8, double loadFactor = 0.75)
  {
    size = 0;

    this->capacity = capacity;
    this->loadFactor = loadFactor;

    buckets = new HashNode<Key> *[capacity];

    for (int i = 0; i < capacity; i++)
    {
      buckets[i] = NULL;
    }
  }

  int hash(int key)
  {
    return key % capacity;
  }

  int hash(std::string key)
  {
    int hash = 0;
    for (char c : key)
    {
      hash += static_cast<int>(c);
    }
    return hash % capacity;
  }

  void insert(Key key, Jedi jedi)
  {
    int index = hash(key);

    HashNode<Key> *node = buckets[index];
    HashNode<Key> *prev = NULL;

    while (node != NULL)
    {
      if (node->key == key)
      {
        node->jedi = jedi;
        return;
      }
      prev = node;
      node = node->next;
    }

    HashNode<Key> *newNode = new HashNode<Key>(key, jedi);

    if (prev == NULL)
    {
      buckets[index] = newNode;
    }
    else
    {
      prev->next = newNode;
    }

    size++;
  }

  Jedi *find(Key key)
  {
    int index = hash(key);

    HashNode<Key> *node = buckets[index];

    while (node != NULL)
    {
      if (node->key == key)
      {
        return &(node->jedi);
      }
      node = node->next;
    }

    return NULL;
  }

  void erase(Key key)
  {
    int index = hash(key);

    HashNode<Key> *prev = NULL;
    HashNode<Key> *node = buckets[index];

    while (node != NULL)
    {
      if (node->key == key)
      {
        if (prev == NULL)
        {
          buckets[index] = node->next;
        }
        else
        {
          prev->next = node->next;
        }

        delete node;
        size--;

        return;
      }

      prev = node;
      node = node->next;
    }
  }

  int getSize()
  {
    return size;
  }

  void resize()
  {
    int newCapacity = capacity * 2;

    HashNode<Key> **newBuckets = new HashNode<Key> *[newCapacity];

    for (int i = 0; i < newCapacity; i++)
    {
      newBuckets[i] = NULL;
    }

    for (int i = 0; i < capacity; i++)
    {
      HashNode<Key> *node = buckets[i];
      while (node != NULL)
      {
        int index = node->key % newCapacity;

        HashNode<Key> *next = node->next;
        node->next = newBuckets[index];

        newBuckets[index] = node;
        node = next;
      }
    }

    delete[] buckets;

    buckets = newBuckets;
    capacity = newCapacity;
  }
};