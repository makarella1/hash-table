#include <iostream>
#include <string>
#include <random>
#include "jedi.h"
#include "hashNode.h"
#include "mySuperLinkedList.h"
#include <unordered_map>

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

long long
generateRandLong(int keysAmount)
{
  std::random_device rd;
  std::mt19937_64 generator(rd());
  std::uniform_int_distribution<long long> distribute(0, keysAmount - 1);

  return distribute(generator);
}

int main()
{
  Jedi jedi = Jedi();

  std::cout << jedi.name;

  HashTable<std::string> stringHashTable;

  stringHashTable.insert(jedi.name, jedi);

  Jedi *found = stringHashTable.find(jedi.name);

  std::cout << found->name;

  // Jedi jedi1 = Jedi();
  // Jedi jedi2 = Jedi();
  // Jedi jedi3 = Jedi();

  // std::cout << jedi1.name << std::endl;
  // std::cout << jedi2.name << std::endl;
  // std::cout << jedi3.name << std::endl;

  // HashTable hashTable;

  // hashTable.insert(1, jedi1);
  // hashTable.insert(1, jedi2);
  // hashTable.insert(1, jedi3);

  // Jedi *found = hashTable.find(1);

  // std::cout << found->name;

  // const int iters = 500000;
  // const int keysAmount = iters * 1;

  // long long *keys = new long long[keysAmount];
  // long long *keysToInsert = new long long[iters];
  // long long *keysToErase = new long long[iters];
  // long long *keysToFind = new long long[iters];
  // for (int i = 0; i < keysAmount; i++)
  // {
  //   keys[i] = generateRandLong(keysAmount);
  // }
  // for (int i = 0; i < iters; i++)
  // {
  //   keysToInsert[i] = keys[generateRandLong(keysAmount)];
  //   keysToErase[i] = keys[generateRandLong(keysAmount)];
  //   keysToFind[i] = keys[generateRandLong(keysAmount)];
  // }

  // HashTable hashTable;

  // clock_t myStart = clock();
  // for (int i = 0; i < iters; i++)
  // {
  //   Jedi jedi = Jedi();

  //   hashTable.insert(keysToInsert[i], jedi);
  // }
  // int myInsertSize = hashTable.getSize();
  // for (int i = 0; i < iters; i++)
  // {
  //   hashTable.erase(keysToErase[i]);
  // }
  // int myEraseSize = hashTable.getSize();
  // int myFoundAmount = 0;
  // for (int i = 0; i < iters; i++)
  // {
  //   if (hashTable.find(keysToFind[i]) != nullptr)
  //   {
  //     myFoundAmount++;
  //   }
  // }
  // clock_t myEnd = clock();
  // float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;

  // test STL hash table:
  // std::unordered_map<long long, Jedi> unorderedMap;
  // clock_t stlStart = clock();
  // for (int i = 0; i < iters; i++)
  // {
  //   Jedi jedi = Jedi();
  //   unorderedMap.insert({keysToInsert[i], jedi});
  // }
  // int stlInsertSize = unorderedMap.size();
  // for (int i = 0; i < iters; i++)
  // {
  //   unorderedMap.erase(keysToErase[i]);
  // }
  // int stlEraseSize = unorderedMap.size();
  // int stlFoundAmount = 0;
  // for (int i = 0; i < iters; i++)
  // {
  //   if (unorderedMap.find(keysToFind[i]) != unorderedMap.end())
  //   {
  //     stlFoundAmount++;
  //   }
  // }
  // clock_t stlEnd = clock();
  // float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;

  // std::cout << "My HashTable:" << std::endl;
  // std::cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize << ", found amount: " << myFoundAmount << std::endl;
  // std::cout << "STL unordered_map:" << std::endl;
  // std::cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize << ", found amount: " << stlFoundAmount << std::endl
  //           << std::endl;
  // delete keys;
  // delete keysToInsert;
  // delete keysToErase;
  // delete keysToFind;
  // if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize && myFoundAmount == stlFoundAmount)
  // {
  //   std::cout << "The lab is completed" << std::endl;
  //   return true;
  // }
  // std::cerr << ":(" << std::endl;
}
