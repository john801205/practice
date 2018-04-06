#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

class BIT
{
  private:
    std::vector<int> tree;

  public:
    BIT(const std::vector<int> &nums): tree()
    {
      this->tree.resize(nums.size()+1);

      for (std::vector<int>::size_type i = 0; i < this->tree.size(); i++)
      {
        this->tree[i] = 0;
      }

      for (std::vector<int>::size_type i = 1; i <= nums.size(); i++)
      {
        this->tree[i] += nums[i-1];

        auto j = i + (i & -i);

        if (j < this->tree.size())
        {
          this->tree[j] += this->tree[i];
        }
      }
    }

    int query(std::vector<int>::size_type i)
    {
      int sum = 0;

      for (auto j = i+1; j != 0; j -= (j & -j))
      {
        sum += this->tree[j];
      }

      return sum;
    }

    void add(std::vector<int>::size_type i, int val)
    {
      for (auto j = i+1; j < this->tree.size(); j += (j & -j))
      {
        this->tree[j] += val;
      }
    }

    int lookup(std::vector<int>::size_type i)
    {
      i++;
      int v = this->tree[i];
      auto x = i - (i & -i);

      for (auto j = i-1; j > x; j -= j & -j)
      {
        v -= this->tree[j];
      }

      return v;
    }
};

class Solution
{
  public:
    std::vector<int> countSmaller(const std::vector<int> &nums)
    {
      std::vector<int> sorted (nums);
      std::sort(std::begin(sorted), std::end(sorted));

      std::unordered_map<int, std::vector<int>::size_type> maps;
      for (std::vector<int>::size_type i = 0; i < sorted.size(); i++)
      {
        maps[sorted[i]] = i;
      }

      std::vector<int> results (nums.size());
      BIT bit (results);

      for (std::vector<int>::size_type i = nums.size(); i-- > 0; )
      {
        std::vector<int>::size_type pos = maps[nums[i]];

        if (pos != 0)
        {
          results[i] = bit.query(pos-1);
        }

        bit.add(pos, 1);
      }

      return results;
    }
};

int main(void)
{
  BIT obj ({1,2,3,4,5});
  assert(obj.lookup(0) == 1);
  assert(obj.lookup(2) == 3);
  assert(obj.query(4) == 15);
  assert(obj.query(3) == 10);
  obj.add(1, 5);
  assert(obj.query(4) == 20);
  assert(obj.query(3) == 15);

  Solution s;
  assert(s.countSmaller({}) == std::vector<int> ({}));
  assert(s.countSmaller({1}) == std::vector<int> ({0}));
  assert(s.countSmaller({5,2,6,1}) == std::vector<int> ({2, 1, 1, 0}));
  assert(s.countSmaller({5,2,6,12,3,7,1,5}) == std::vector<int> ({3,1,3,4,1,2,0,0}));
  assert(s.countSmaller({1,2,3,4,5,6,7}) == std::vector<int> ({0,0,0,0,0,0,0}));
  assert(s.countSmaller({7,6,5,4,3,2,1}) == std::vector<int> ({6,5,4,3,2,1,0}));
  assert(s.countSmaller({1,2,2,2,1,1}) == std::vector<int> ({0,2,2,2,0,0}));
  return 0;
}
