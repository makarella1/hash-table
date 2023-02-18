#include "jedi.h"

template <typename Key>
struct OpenAddressingHashTable
{
  int size;
  int capacity;

  double loadFactor;

  Key *keys;
  Jedi *values;

  bool *occupied;

  OpenAdressingHashTable(int capacity = 8, double loadFactor = 0.75)
  {
    size = 0;
    this->capacity = capacity;
    this->loadFactor = loadFactor;

    keys = new Key[capacity];
    values = new Jedi[capacity];
    occupied = new bool[capacity];

    for (int i = 0; i < capacity; i++)
    {
      occupied[i] = false;
    }
  }

  int hash(int key)
  {
    return key % capacity;
  }

  int hash(std::string key)
  {
    int hash = 0;

    for (char c : key)
    {
      hash += static_cast<int>(c);
    }

    return hash % capacity;
  }

  int probe(int index)
  {
    int step = 1;

    while (occupied[index])
    {
      index = (index + step * step) % capacity;
      step++;
    }

    return index;
  }

  void insert(Key key, Jedi jedi)
  {
    if (size >= capacity * loadFactor)
    {
      resize();
    }

    int index = hash(key);
    index = probe(index);

    keys[index] = key;
    values[index] = jedi;
    occupied[index] = true;

    size++;
  }

  Jedi *find(Key key)
  {
    int index = hash(key);
    int step = 1;

    while (occupied[index])
    {
      if (keys[index] == key)
      {
        return &values[index];
      }
      index = (index + step * step) % capacity;
      step++;
    }

    return NULL;
  }

  void erase(Key key)
  {
    int index = hash(key);
    int step = 1;

    while (occupied[index])
    {
      if (keys[index] == key)
      {
        occupied[index] = false;
        size--;
        return;
      }

      index = (index + step * step) % capacity;

      step++;
    }
  }

  int getSize()
  {
    return size;
  }

  void resize()
  {
    int newCapacity = capacity * 2;

    Key *newKeys = new Key[newCapacity];
    Jedi *newValues = new Jedi[newCapacity];
    bool *newOccupied = new bool[newCapacity];

    for (int i = 0; i < newCapacity; i++)
    {
      newOccupied[i] = false;
    }

    for (int i = 0; i < capacity; i++)
    {
      if (occupied[i])
      {
        int newIndex = hash(keys[i]);
        newIndex = probe(newIndex);

        newKeys[newIndex] = keys[i];
        newValues[newIndex] = values[i];
        newOccupied[newIndex] = true;
      }
    }

    delete[] keys;
    delete[] values;
    delete[] occupied;

    keys = newKeys;
    values = newValues;
    occupied = newOccupied;

    capacity = newCapacity;
  }
};