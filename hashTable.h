#include "jedi.h"
#include "hashNode.h"
#include "mySuperLinkedList.h"

const int LOAD_FACTOR = 9;

template <typename Key>
struct HashTable
{
private:
  MySuperLinkedList<Key> *buckets;

  int size;

  int bucketsLength;

  int hash(int key)
  {
    return key % bucketsLength;
  }

  int hash(std::string key)
  {
    int hash = 0;
    for (char c : key)
    {
      hash += static_cast<int>(c);
    }
    return hash % bucketsLength;
  }

  double loadFactor()
  {
    return static_cast<double>(size) / bucketsLength;
  }

  void resize()
  {
    int newLength = bucketsLength * 2;

    MySuperLinkedList<Key> *newBuckets = new MySuperLinkedList<Key>[newLength];

    for (int i = 0; i < bucketsLength; i++)
    {
      HashNode<Key> *current = buckets[i].head;

      while (current != nullptr)
      {
        HashNode<Key> *newNode = new HashNode<Key>(current->key, current->jedi);

        newBuckets[hash(current->key)].pushBack(*newNode);
        current = current->next;
      }
    }

    delete[] buckets;
    buckets = newBuckets;

    bucketsLength = newLength;
  }

public:
  HashTable()
  {
    size = 0;
    bucketsLength = 8;
    buckets = new MySuperLinkedList<Key>[bucketsLength];
  }

  void insert(Key key, Jedi &jedi)
  {
    if (loadFactor() >= LOAD_FACTOR)
    {
      resize();
    }

    int index = hash(key);

    HashNode<Key> *current = buckets[index].head;

    while (current != nullptr)
    {
      if (current->key == key)
      {
        current->jedi = jedi;
        return;
      }
      current = current->next;
    }

    HashNode<Key> *newNode = new HashNode<Key>(key, jedi);
    buckets[index].pushBack(*newNode);
    ++size;
  }

  Jedi *find(Key key)
  {
    int index = hash(key);
    HashNode<Key> *current = buckets[index].head;

    while (current != nullptr)
    {
      if (current->key == key)
      {
        return &(current->jedi);
      }

      current = current->next;
    }

    return NULL;
  }

  void erase(Key key)
  {
    int index = hash(key);

    HashNode<Key> *current = buckets[index].head;
    HashNode<Key> *prev = nullptr;

    while (current != nullptr)
    {
      if (current->key == key)
      {
        if (prev == nullptr)
        {
          buckets[index].popFront();
        }
        else
        {
          prev->next = current->next;
          delete current;
        }
        --size;
        break;
      }

      prev = current;
      current = current->next;
    }
  }

  int getSize()
  {
    return size;
  }
};