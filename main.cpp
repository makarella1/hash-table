#include <iostream>
#include <random>
#include <string>
#include <cstdlib>
#include "jedi.h"

const long long MIN_13_DIGIT_NUM = 1000000000000;
const long long MAX_13_DIGIT_NUM = 9999999999999;

const int BUCKETS_LENGTH = 10000;

struct HashNode
{
  Jedi jediData;
  int key;

  HashNode(int keyValue, Jedi jedi)
  {
    jediData = jedi;
    key = keyValue;
  }
};

int main()
{
  // std::random_device rd;
  // std::mt19937_64 generator(rd());
  // std::uniform_int_distribution<uint64_t> distribute(MIN_13_DIGIT_NUM, MAX_13_DIGIT_NUM);

  Jedi firstJedi = Jedi();
  Jedi secondJedi = Jedi();

  std::cout << firstJedi.name << std::endl;
  std::cout << secondJedi.name << std::endl;
}