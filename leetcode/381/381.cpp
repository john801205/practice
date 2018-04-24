#include <cassert>
#include <iostream>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class RandomizedCollection
{
  private:
    std::vector<int> sets;
    std::unordered_map<int, std::unordered_set<std::vector<int>::size_type>> indexes;
    std::random_device rd;
    std::mt19937 rng;

  public:
    /** Initialize your data structure here. */
    RandomizedCollection(): sets(), indexes(), rd(), rng(rd())
    {
    }

    /** Inserts a value to the collection. Returns true
     * if the collection did not already contain the specified element. */
    bool insert(int val)
    {
      bool nonexistent = (indexes.find(val) == indexes.end());

      indexes[val].emplace(sets.size());
      sets.emplace_back(val);

      return nonexistent;
    }

    /** Removes a value from the collection. Returns true
     * if the collection contained the specified element. */
    bool remove(int val)
    {
      if (indexes.find(val) == indexes.end())
        return false;

      if (sets.back() != val)
      {
        const auto index = *indexes[val].begin();
        indexes[val].erase(index);
        if (indexes[val].empty())
          indexes.erase(val);

        const auto index2 = sets.size()-1;
        indexes[sets[index2]].erase(index2);
        indexes[sets[index2]].emplace(index);

        std::swap(sets[index], sets[index2]);
        sets.pop_back();
      }
      else
      {
        const auto index = sets.size()-1;
        indexes[val].erase(index);
        if (indexes[val].empty())
          indexes.erase(val);

        sets.pop_back();
      }

      return true;
    }

    /** Get a random element from the collection. */
    int getRandom()
    {
      std::uniform_int_distribution<int> uni(0, sets.size()-1);
      auto index = uni(rng);

      return sets[index];
    }
};

int main()
{
  /**
   * Your RandomizedCollection object will be instantiated and called as such:
   * RandomizedCollection obj = new RandomizedCollection();
   * bool param_1 = obj.insert(val);
   * bool param_2 = obj.remove(val);
   * int param_3 = obj.getRandom();
   */
  RandomizedCollection obj;
  assert(obj.insert(1) == true);
  assert(obj.insert(1) == false);
  assert(obj.insert(2) == true);
  assert(obj.remove(1) == true);
  assert(obj.remove(1) == true);
  assert(obj.remove(1) == false);
  assert(obj.getRandom() == 2);
  assert(obj.getRandom() == 2);

  RandomizedCollection obj2;
  assert(obj2.insert(0) == true);
  assert(obj2.remove(0) == true);
  assert(obj2.insert(-1) == true);
  assert(obj2.remove(0) == false);
  assert(obj2.getRandom() == -1);
  assert(obj2.getRandom() == -1);
  assert(obj2.getRandom() == -1);

  return 0;
}
