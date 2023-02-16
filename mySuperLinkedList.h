#pragma once

#include "hashNode.h"

struct MySuperLinkedList
{
private:
  int size;
  bool isEmpty();

public:
  MySuperLinkedList();

  HashNode *head;

  void pushFront(HashNode hashNode);

  void pushBack(HashNode &hashNode);

  HashNode get(int index);

  HashNode popFront();

  HashNode popBack();

  int getSize();

  void print();
};