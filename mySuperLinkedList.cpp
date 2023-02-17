#include <iostream>
#include "mySuperLinkedList.h"
#include "hashNode.h"

template <typename Key>
MySuperLinkedList<Key>::MySuperLinkedList()
{
  head = nullptr;
  size = 0;
}

template <typename Key>
bool MySuperLinkedList<Key>::isEmpty()
{
  return head == nullptr;
}

template <typename Key>
void MySuperLinkedList<Key>::pushFront(HashNode<Key> hashNode)
{
  HashNode<Key> *newHead = new HashNode<Key>(hashNode);

  newHead->next = head;

  head = newHead;

  ++size;
}

template <typename Key>
void MySuperLinkedList<Key>::pushBack(HashNode<Key> &hashNode)
{
  if (isEmpty())
  {
    head = new HashNode<Key>(hashNode);
  }
  else
  {
    HashNode<Key> *newTail = new HashNode<Key>(hashNode);

    HashNode<Key> *current = head;

    while (current->next != nullptr)
    {
      current = current->next;
    }

    current->next = newTail;
    newTail->next = nullptr;
  }
  ++size;
}

template <typename Key>
HashNode<Key> MySuperLinkedList<Key>::get(int index)
{
  if (index <= 0 && index > size)
  {
    std::cerr << "Can you just leave me alone?" << std::endl;
    exit(1);
  }

  HashNode<Key> *current = head;

  for (int i = 0; i < index; i++)
  {
    current = current->next;
  }

  return *current;
}

template <typename Key>
HashNode<Key> MySuperLinkedList<Key>::popFront()
{
  if (isEmpty())
  {
    std::cerr << "You're hopeless, there's nothing I can give you!" << std::endl;
    exit(1);
  }

  HashNode<Key> *oldHead = head;
  HashNode<Key> result = *head;

  head = head->next;

  delete oldHead;

  --size;

  return result;
}

template <typename Key>
HashNode<Key> MySuperLinkedList<Key>::popBack()
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

  HashNode<Key> *current = head;

  while (current->next->next != nullptr)
  {
    current = current->next;
  }

  HashNode<Key> result = *(current->next);

  delete current->next;
  current->next = nullptr;

  --size;

  return result;
}

template <typename Key>
int MySuperLinkedList<Key>::getSize()
{
  return size;
}

template <typename Key>
void MySuperLinkedList<Key>::print()
{
  HashNode<Key> *current = head;

  while (current != nullptr)
  {
    std::cout << "Jedi's name: " << current->jedi.name << std::endl;
    std::cout << "Jedi's lightsaber color: " << current->jedi.lightsaberColor << std::endl;
    std::cout << "Number of jedi's padawans: " << current->jedi.numOfPadawans << std::endl;

    std::cout << "\n";

    current = current->next;
  }
}