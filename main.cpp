#include <iostream>
#include <string>
#include <random>
#include "jedi.h"
#include "hashTable.h"
#include "openAddressingHashTable.h"
#include <unordered_map>

long long
generateRandLong(int keysAmount);

int main()
{
  const int iters = 1000;
  const int keysAmount = iters * 1;
  // generate random keys:
  long long *keys = new long long[keysAmount];
  long long *keysToInsert = new long long[iters];
  long long *keysToErase = new long long[iters];
  long long *keysToFind = new long long[iters];
  for (int i = 0; i < keysAmount; i++)
  {
    keys[i] = generateRandLong(keysAmount);
  }
  for (int i = 0; i < iters; i++)
  {
    keysToInsert[i] = keys[generateRandLong(keysAmount)];
    keysToErase[i] = keys[generateRandLong(keysAmount)];
    keysToFind[i] = keys[generateRandLong(keysAmount)];
  }
  // test my HashTable:
  HashTable<int> hashTable;
  clock_t myStart = clock();
  for (int i = 0; i < iters; i++)
  {
    hashTable.insert(keysToInsert[i], Jedi());
  }
  int myInsertSize = hashTable.getSize();
  for (int i = 0; i < iters; i++)
  {
    hashTable.erase(keysToErase[i]);
  }
  int myEraseSize = hashTable.getSize();
  int myFoundAmount = 0;
  for (int i = 0; i < iters; i++)
  {
    if (hashTable.find(keysToFind[i]) != NULL)
    {
      myFoundAmount++;
    }
  }
  clock_t myEnd = clock();
  float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;
  // test STL hash table:
  std::unordered_map<long long, Jedi> unorderedMap;
  clock_t stlStart = clock();
  for (int i = 0; i < iters; i++)
  {
    unorderedMap.insert({keysToInsert[i], Jedi()});
  }
  int stlInsertSize = unorderedMap.size();
  for (int i = 0; i < iters; i++)
  {
    unorderedMap.erase(keysToErase[i]);
  }
  int stlEraseSize = unorderedMap.size();
  int stlFoundAmount = 0;
  for (int i = 0; i < iters; i++)
  {
    if (unorderedMap.find(keysToFind[i]) != unorderedMap.end())
    {
      stlFoundAmount++;
    }
  }
  clock_t stlEnd = clock();
  float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;
  std::cout << "My HashTable:" << std::endl;
  std::cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize << ", found amount: " << myFoundAmount << std::endl;
  std::cout << "STL unordered_map:" << std::endl;
  std::cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize << ", found amount: " << stlFoundAmount << std::endl
            << std::endl;
  delete keys;
  delete keysToInsert;
  delete keysToErase;
  delete keysToFind;
  if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize && myFoundAmount == stlFoundAmount)
  {
    std::cout << "The lab is completed" << std::endl;
    return true;
  }
  std::cerr << ":(" << std::endl;
  return false;
}

long long generateRandLong(int keysAmount)
{
  std::random_device rd;
  std::mt19937_64 generator(rd());
  std::uniform_int_distribution<long long> distribute(0, keysAmount - 1);

  return distribute(generator);
}
