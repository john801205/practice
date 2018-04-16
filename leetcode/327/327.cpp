#include <cassert>
#include <climits>
#include <iostream>
#include <set>
#include <vector>

class BIT
{
  private:
    std::vector<long long> tree;

  public:
    BIT(std::vector<long long>::size_type size): tree(size+1, 0) {}

    void add(std::vector<long long>::size_type pos, int val)
    {
      for (std::vector<long long>::size_type i = pos+1; i < tree.size(); i += i & -i)
      {
        tree[i] += val;
      }
    }

    long long query(std::vector<long long>::size_type pos)
    {
      long long sum = 0;

      for (std::vector<long long>::size_type i = pos+1; i != 0; i -= i&-i)
      {
        sum += tree[i];
      }

      return sum;
    }
};

class Solution
{
  public:
    int countRangeSum(const std::vector<int>& nums, const int lower, const int upper)
    {
      std::set<long long> sum_set;
      long long sum = 0;

      for (const auto &num: nums)
      {
        sum += num;
        sum_set.emplace(sum);
      }

      std::vector<long long> sums (sum_set.begin(), sum_set.end());

      BIT bit(sums.size());
      int count = 0;

      sum = 0;
      for (const auto &num: nums)
      {
        sum += num;

        if (sum >= lower && sum <= upper)
          count += 1;

        auto pos = std::lower_bound(sums.begin(), sums.end(), sum-lower+1);
        count += bit.query(pos - sums.begin() - 1);

        pos = std::lower_bound(sums.begin(), sums.end(), sum-upper);
        count -= bit.query(pos - sums.begin() - 1);

        pos = std::lower_bound(sums.begin(), sums.end(), sum);
        bit.add(pos - sums.begin(), 1);
      }

      return count;
    }
};

int main(void)
{
  Solution s;
  assert(s.countRangeSum({}, -2, 2) == 0);
  assert(s.countRangeSum({-3}, -2, 2) == 0);
  assert(s.countRangeSum({-2}, -2, 2) == 1);
  assert(s.countRangeSum({-2,5,-1}, -2, 2) == 3);
  assert(s.countRangeSum({-2,5,-1,1,2,3,4}, -2, 2) == 7);
  assert(s.countRangeSum({-2,5,-1,1,2,3,4}, -3, 2) == 7);
  assert(s.countRangeSum({-2,5,-1,1,2,3,4}, -3, 4) == 13);
  assert(s.countRangeSum({2147483647,-2147483648,-1,0}, -1, 0) == 4);

  return 0;
}
