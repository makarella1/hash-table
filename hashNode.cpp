#include "hashNode.h"

HashNode::HashNode(int keyValue, Jedi jediData)
{
  jedi = jediData;
  key = keyValue;
  next = nullptr;
}