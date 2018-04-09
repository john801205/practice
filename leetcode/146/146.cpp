#include <cassert>
#include <iostream>
#include <unordered_map>

struct Node
{
  int key, value;
  Node *prev, *next;

  Node(int key, int value): key(key), value(value), prev(nullptr), next(nullptr) {}
};

class LRUCache
{
  private:
    int capacity, usage;
    Node *head, *tail;
    std::unordered_map<int, Node *> map;

  public:
    LRUCache(int capacity): capacity(capacity), usage(0), head(nullptr), tail(nullptr), map()
    {
    }

    int get(int key)
    {
      auto search = map.find(key);
      if (search == map.end())
      {
        return -1;
      }

      Node *current = search->second;

      if (current->prev == nullptr)
      {
        return current->value;
      }

      current->prev->next = current->next;
      if (current->next != nullptr)
      {
        current->next->prev = current->prev;
      }
      else
      {
        tail = current->prev;
      }

      current->next = head;
      current->prev = nullptr;
      head->prev = current;
      head = current;

      return current->value;
    }

    void put(int key, int value)
    {
      if (get(key) != -1)
      {
        map[key]->value = value;
        return;
      }

      if (usage == capacity)
      {
        map.erase(tail->key);
        tail = tail->prev;
        if (tail != nullptr)
        {
          delete tail->next;
          tail->next = nullptr;
        }
        usage--;
      }

      Node *current = new Node(key, value);
      map[key] = current;

      current->next = head;
      if (head != nullptr)
      {
        head->prev = current;
      }
      head = current;
      if (tail == nullptr)
      {
        tail = current;
      }

      usage++;
    }
};

int main(void)
{
  LRUCache cache(2);

  cache.put(1, 1);
  cache.put(2, 2);
  assert(cache.get(1) == 1);
  cache.put(3, 3);
  assert(cache.get(2) == -1);
  cache.put(4, 4);
  assert(cache.get(1) == -1);
  assert(cache.get(3) == 3);
  assert(cache.get(4) == 4);

  LRUCache cache2(1);
  cache2.put(2, 1);
  assert(cache2.get(2) == 1);
  cache2.put(3, 2);
  assert(cache2.get(2) == -1);
  assert(cache2.get(3) == 2);

  LRUCache cache3(2);
  assert(cache3.get(2) == -1);
  cache3.put(2, 6);
  assert(cache3.get(1) == -1);
  cache3.put(1, 5);
  cache3.put(1, 2);
  assert(cache3.get(1) == 2);
  assert(cache3.get(2) == 6);
  return 0;
}
