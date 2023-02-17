#pragma once

#include "hashNode.h"

template <typename Key>
struct MySuperLinkedList
{
private:
  int size;
  bool isEmpty();

public:
  MySuperLinkedList();

  HashNode<Key> *head;

  void pushFront(HashNode<Key> hashNode);

  void pushBack(HashNode<Key> &hashNode);

  HashNode<Key> get(int index);

  HashNode<Key> popFront();

  HashNode<Key> popBack();

  int getSize();

  void print();
};