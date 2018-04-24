#include <cassert>
#include <iostream>
#include <random>
#include <vector>
#include <unordered_map>

class RandomizedSet
{
  private:
    std::vector<int> sets;
    std::unordered_map<int, std::vector<int>::size_type> indexes;
    std::random_device rd;
    std::mt19937 rng;

  public:
    /** Initialize your data structure here. */
    RandomizedSet(): sets(), indexes(), rd(), rng(rd())
    {
    }

    /** Inserts a value to the set. Returns true if the set did not already
     * contain the specified element. */
    bool insert(int val)
    {
      if (indexes.find(val) != indexes.end())
        return false;

      indexes[val] = sets.size();
      sets.emplace_back(val);
      return true;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val)
    {
      if (indexes.find(val) == indexes.end())
        return false;

      indexes[sets.back()] = indexes[val];
      std::swap(sets.back(), sets[indexes[val]]);
      sets.pop_back();
      indexes.erase(val);
      return true;
    }

    /** Get a random element from the set. */
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
   * Your RandomizedSet object will be instantiated and called as such:
   * RandomizedSet obj = new RandomizedSet();
   * bool param_1 = obj.insert(val);
   * bool param_2 = obj.remove(val);
   * int param_3 = obj.getRandom();
   */
  RandomizedSet obj;
  assert(obj.insert(1) == true);
  assert(obj.remove(2) == false);
  assert(obj.insert(2) == true);
  assert(obj.remove(1) == true);
  assert(obj.insert(2) == false);

  RandomizedSet obj2;
  assert(obj2.insert(0) == true);
  assert(obj2.remove(0) == true);
  assert(obj2.insert(-1) == true);
  assert(obj2.remove(0) == false);
  assert(obj2.getRandom() == -1);
  assert(obj2.getRandom() == -1);
  assert(obj2.getRandom() == -1);
  assert(obj2.getRandom() == -1);


  return 0;
}
