#pragma once

#include "jedi.h"

template <typename Key>
struct HashNode
{
  Jedi jedi;
  Key key;
  HashNode *next;

  HashNode(Key key, Jedi jedi)
  {
    this->jedi = jedi;
    this->key = key;
    next = nullptr;
  };
};