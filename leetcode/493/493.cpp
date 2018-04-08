#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

class BIT
{
  private:
    std::vector<int> tree;

  public:
    BIT(const std::vector<int>::size_type size): tree()
    {
      tree.resize(size+1);

      for (std::vector<int>::size_type i = 0; i < this->tree.size(); i++)
      {
        this->tree[i] = 0;
      }
    }

    BIT(const std::vector<int> &nums): tree()
    {
      tree.resize(nums.size()+1);

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

    void add(std::vector<int>::size_type i, int val)
    {
      i++;
      while (i < this->tree.size())
      {
        this->tree[i] += val;
        i = i + (i & -i);
      }
    }

    int query(std::vector<int>::size_type i)
    {
      i++;

      int sum = 0;
      while (i > 0)
      {
        sum += this->tree[i];
        i = i - (i & -i);
      }

      return sum;
    }
};

class Solution
{
  public:
    int reversePairs(const std::vector<int> &nums)
    {
      std::vector<int> sorted (nums);
      std::sort(std::begin(sorted), std::end(sorted));

      int pairs = 0;
      BIT bit(nums.size());

      for (std::vector<int>::size_type i = nums.size(); i-- > 0; )
      {
        // std::cerr << i << ' ' << nums[i] << '\n';
        auto pos = lowerThanOrEqual(sorted, 0, sorted.size()-1, std::floor((nums[i] - 0.1)/2.0));
        pairs += bit.query(pos);
        // std::cerr << "pairs: " << bit.query(pos) << '\n';

        pos = lowerThanOrEqual(sorted, 0, sorted.size()-1, nums[i]);
        bit.add(pos, 1);
      }

      return pairs;
    }

    std::vector<int>::size_type lowerThanOrEqual(const std::vector<int> &nums,
                                                 const std::vector<int>::size_type left,
                                                 const std::vector<int>::size_type right,
                                                 const int value)
    {
      // std::cerr << left << '\t' << right << '\t' << value << '\n';
      if (right == std::numeric_limits<std::vector<int>::size_type>::max()
          || left > right)
      {
        return std::numeric_limits<std::vector<int>::size_type>::max();
      }

      if (left == right)
      {
        if (nums[left] <= value)
        {
          return left;
        }
        else
        {
          return std::numeric_limits<std::vector<int>::size_type>::max();
        }
      }

      auto middle = left + (right - left) / 2;

      if (nums[middle] > value)
      {
        return lowerThanOrEqual(nums, left, middle-1, value);
      }

      auto pos = lowerThanOrEqual(nums, middle+1, right, value);
      if (pos == std::numeric_limits<std::vector<int>::size_type>::max())
      {
        return middle;
      }
      else
      {
        return pos;
      }
    }
};

int main(void)
{
  BIT obj ({1,2,3,4,5});
  assert(obj.query(4) == 15);
  assert(obj.query(3) == 10);
  obj.add(1, 5);
  assert(obj.query(4) == 20);
  assert(obj.query(3) == 15);

  Solution s;
  assert(s.reversePairs({}) == 0);
  assert(s.reversePairs({1,3,2,3,1}) == 2);
  assert(s.reversePairs({2,4,3,5,1}) == 3);
  assert(s.reversePairs({1,2,3,4,5}) == 0);

  return 0;
}
