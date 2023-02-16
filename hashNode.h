#pragma once

#include "jedi.h"

struct HashNode
{
  Jedi jedi;
  int key;
  HashNode *next;

  HashNode(int keyValue, Jedi jedi);
};