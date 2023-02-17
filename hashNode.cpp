#include "hashNode.h"

template <typename Key>
HashNode<Key>::HashNode(Key key, Jedi jediData)
{
  jedi = jediData;
  this->key = key;
  next = nullptr;
}