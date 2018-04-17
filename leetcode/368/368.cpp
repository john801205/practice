#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>

class Solution
{
  public:
    std::vector<int> largestDivisibleSubset(std::vector<int> nums)
    {
      if (nums.size() <= 1)
        return nums;

      std::sort(std::begin(nums), std::end(nums));

      std::vector<int> dp (nums.size());
      std::vector<std::vector<int>::size_type> parent (nums.size());
      std::vector<int>::size_type maxpos = 0;

      for (std::vector<int>::size_type i = 0; i < nums.size(); i++)
      {
        std::vector<int>::size_type tempmax = i;

        for (std::vector<int>::size_type j = 0; j < i; j++)
        {
          if (nums[i] % nums[j] == 0 && dp[j] > dp[tempmax])
          {
            tempmax = j;
          }
        }

        dp[i] = dp[tempmax]+1;
        parent[i] = tempmax;

        if (dp[i] > dp[maxpos])
          maxpos = i;
      }

      std::vector<int> result;

      while (maxpos !=  parent[maxpos])
      {
        result.emplace_back(nums[maxpos]);
        maxpos = parent[maxpos];
      }
      result.emplace_back(nums[maxpos]);
      std::reverse(std::begin(result), std::end(result));

      return result;
    }
};

int main(void)
{
  Solution s;
  assert(s.largestDivisibleSubset({}) == std::vector<int> ({}));
  assert(s.largestDivisibleSubset({1}) == std::vector<int> ({1}));
  assert(s.largestDivisibleSubset({1,2,3}) == std::vector<int> ({1,2}));
  assert(s.largestDivisibleSubset({1,2,4,8}) == std::vector<int> ({1,2,4,8}));
  assert(s.largestDivisibleSubset({1,2,3,4,5,6,7,8}) == std::vector<int> ({1,2,4,8}));
  assert(s.largestDivisibleSubset({1,2,3,4,5,6,7,8,9,81,243}) == std::vector<int> ({1,3,9,81,243}));
  assert(s.largestDivisibleSubset({9,8,7,6,5,4,3,2,1}) == std::vector<int> ({1,2,4,8}));
  return 0;
}
