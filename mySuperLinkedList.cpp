#include <iostream>
#include "mySuperLinkedList.h"
#include "hashNode.h"

MySuperLinkedList::MySuperLinkedList()
{
  head = nullptr;
  size = 0;
}

bool MySuperLinkedList::isEmpty()
{
  return head == nullptr;
}

void MySuperLinkedList::pushFront(HashNode hashNode)
{
  HashNode *newHead = new HashNode(hashNode);

  newHead->next = head;

  head = newHead;

  ++size;
}

void MySuperLinkedList::pushBack(HashNode &hashNode)
{
  if (isEmpty())
  {
    head = new HashNode(hashNode);
  }
  else
  {
    HashNode *newTail = new HashNode(hashNode);

    HashNode *current = head;

    while (current->next != nullptr)
    {
      current = current->next;
    }

    current->next = newTail;
    newTail->next = nullptr;
  }
  ++size;
}

HashNode MySuperLinkedList::get(int index)
{
  if (index <= 0 && index > size)
  {
    std::cerr << "Can you just leave me alone?" << std::endl;
    exit(1);
  }

  HashNode *current = head;

  for (int i = 0; i < index; i++)
  {
    current = current->next;
  }

  return *current;
}

HashNode MySuperLinkedList::popFront()
{
  if (isEmpty())
  {
    std::cerr << "You're hopeless, there's nothing I can give you!" << std::endl;
    exit(1);
  }

  HashNode *oldHead = head;
  HashNode result = *head;

  head = head->next;

  delete oldHead;

  --size;

  return result;
}

HashNode MySuperLinkedList::popBack()
{
  if (isEmpty())
  {
    std::cerr << "What do you expect me to give you?" << std::endl;
    exit(1);
  }
  else if (head->next == nullptr)
  {
    return popFront();
  }

  HashNode *current = head;

  while (current->next->next != nullptr)
  {
    current = current->next;
  }

  HashNode result = *(current->next);

  delete current->next;
  current->next = nullptr;

  --size;

  return result;
}

int MySuperLinkedList::getSize()
{
  return size;
}

void MySuperLinkedList::print()
{
  HashNode *current = head;

  while (current != nullptr)
  {
    std::cout << "Jedi's name: " << current->jedi.name << std::endl;
    std::cout << "Jedi's lightsaber color: " << current->jedi.lightsaberColor << std::endl;
    std::cout << "Number of jedi's padawans: " << current->jedi.numOfPadawans << std::endl;

    std::cout << "\n";

    current = current->next;
  }
}