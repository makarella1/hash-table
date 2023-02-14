#include <iostream>
#include "mySuperLinkedList.h"
#include "jedi.h"

Node::Node(Jedi jedi)
{
  jedi = jedi;
  next = nullptr;
}

MySuperLinkedList::MySuperLinkedList()
{
  head = nullptr;
  size = 0;
}

bool MySuperLinkedList::isEmpty()
{
  return head == nullptr;
}

void MySuperLinkedList::pushFront(Jedi jedi)
{
  Node *newHead = new Node(jedi);

  newHead->next = head;

  head = newHead;

  ++size;
}

void MySuperLinkedList::pushBack(Jedi jedi)
{
  if (isEmpty())
  {
    head = new Node(jedi);
  }
  else
  {
    Node *newTail = new Node(jedi);

    Node *current = head;

    while (current->next != nullptr)
    {
      current = current->next;
    }

    current->next = newTail;
  }
  ++size;
}

Jedi MySuperLinkedList::get(int index)
{
  if (index <= 0 && index > size)
  {
    std::cerr << "Can you just leave me alone?" << std::endl;
    exit(1);
  }

  Node *current = head;

  for (int i = 0; i < index; i++)
  {
    current = current->next;
  }

  return current->jedi;
}

Jedi MySuperLinkedList::popFront()
{
  if (isEmpty())
  {
    std::cerr << "You're hopeless, there's nothing I can give you!" << std::endl;
    exit(1);
  }

  Node *newHead = head->next;

  Jedi headData = head->jedi;

  delete head;

  head = newHead;

  --size;

  return headData;
}

Jedi MySuperLinkedList::popBack()
{
  if (isEmpty())
  {
    std::cerr << "What do you expect me to give you?" << std::endl;
    exit(1);
  }
  else if (head->next == nullptr)
  {
    Jedi headData = head->jedi;

    delete head;

    head = nullptr;

    return headData;
  }

  Node *current = head;

  while (current->next->next != nullptr)
  {
    current = current->next;
  }

  Jedi lastData = current->next->jedi;

  delete current->next;

  current->next = nullptr;

  --size;

  return lastData;
}

int MySuperLinkedList::getSize()
{
  return size;
}

void MySuperLinkedList::print()
{
  Node *current = head;

  while (current != nullptr)
  {
    std::cout << "Jedi's name: " << current->jedi.name << std::endl;
    std::cout << "Jedi's lightsaber color: " << current->jedi.lightsaberColor << std::endl;
    std::cout << "Number of jedi's padawans: " << current->jedi.numOfPadawans << std::endl;

    std::cout << "\n";

    current = current->next;
  }
}