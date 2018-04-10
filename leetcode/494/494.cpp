#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

class Solution
{
  public:
    int findTargetSumWays(const std::vector<int> &nums, int S)
    {
      int sum = std::accumulate(std::begin(nums), std::end(nums), 0);

      if (nums.size() == 0)
      {
        return 0;
      }

      if (S > sum || S < -sum)
      {
        return 0;
      }

      std::vector<int> dp (2*sum+1, 0);
      dp[nums[0]+sum] = 1;
      dp[-nums[0]+sum] += 1;

      for (std::vector<int>::size_type i = 1; i < nums.size(); i++)
      {
        std::vector<int> temp (2*sum+1, 0);

        for (std::vector<int>::size_type j = 0; j+nums[i] < temp.size(); j++)
        {
          temp[j+nums[i]] += dp[j];
        }

        for (int j = dp.size()-1; j >= nums[i]; j--)
        {
          temp[j-nums[i]] += dp[j];
        }

        dp = temp;
      }

      return dp[S+sum];
    }
};

int main(void)
{
  Solution s;
  assert(s.findTargetSumWays({1,1,1,1,1}, 3) == 5);
  assert(s.findTargetSumWays({1,0}, 1) == 2);
  assert(s.findTargetSumWays({0,0,0,0,0,0,0,0,1}, 1) == 256);
  return 0;
}
