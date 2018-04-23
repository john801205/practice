#include <cassert>
#include <iostream>
#include <list>
#include <unordered_map>

class LFUCache
{
  private:
    std::unordered_map<int, std::list<std::tuple<int,int,int>>> list;
    std::unordered_map<int, std::list<std::tuple<int,int,int>>::iterator> map;
    int min_freq;
    int capacity, count;

  public:
    LFUCache(int capacity): list(), map(), min_freq(0), capacity(capacity), count(0)
    {
    }

    int get(int key)
    {
      if (map.find(key) == map.end())
        return -1;

      const auto tuple = *map[key];
      const auto value = std::get<1>(tuple);
      const auto freq  = std::get<2>(tuple);

      list[freq].erase(map[key]);

      if (min_freq == freq && list[freq].empty())
        min_freq++;

      const auto ptr = list[freq+1].insert(std::begin(list[freq+1]), {key, value, freq+1});
      map[key] = ptr;

      return value;
    }

    void put(int key, int value)
    {
      if (capacity <= 0)
        return;

      if (map.find(key) != map.end())
      {
        std::get<1>(*map[key]) = value;
        get(key);
      }
      else
      {
        if (count < capacity)
        {
          count++;
        }
        else
        {
          const auto tuple = list[min_freq].back();
          const auto key = std::get<0>(tuple);

          list[min_freq].pop_back();
          map.erase(key);
        }

        min_freq = 0;

        const auto ptr = list[0].insert(std::begin(list[0]), {key, value, 0});
        map[key] = ptr;
      }
    }
};

int main()
{
  /**
   * Your LFUCache object will be instantiated and called as such:
   * LFUCache obj = new LFUCache(capacity);
   * int param_1 = obj.get(key);
   * obj.put(key,value);
   */

  LFUCache cache(2);

  cache.put(1, 1);
  cache.put(2, 2);
  assert(cache.get(1) == 1);
  cache.put(3, 3);
  assert(cache.get(2) == -1);
  assert(cache.get(3) == 3);
  cache.put(4, 4);
  assert(cache.get(1) == -1);
  assert(cache.get(3) == 3);
  assert(cache.get(4) == 4);
  cache.put(4, 2);
  assert(cache.get(4) == 2);

  LFUCache cache2(0);
  cache2.put(1, 1);
  assert(cache2.get(1) == -1);

  return 0;
}
