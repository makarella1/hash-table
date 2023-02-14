#pragma once

#include "jedi.h"

struct Node
{
  Jedi jedi;
  Node *next;

  Node(Jedi jedi);
};

struct MySuperLinkedList
{
private:
  Node *head;
  int size;
  bool isEmpty();

public:
  MySuperLinkedList();

  void pushFront(Jedi jedi);

  void pushBack(Jedi jedi);

  Jedi get(int index);

  Jedi popFront();

  Jedi popBack();

  int getSize();

  void print();
};