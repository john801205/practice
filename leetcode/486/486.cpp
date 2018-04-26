#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    bool PredictTheWinner(const std::vector<int> &nums)
    {
      std::vector<std::vector<long>> dp  (nums.size()+2, std::vector<long> (nums.size()+2, 0));

      for (std::vector<long>::size_type i = 0; i < nums.size(); i++)
        dp[i+1][i+1] = nums[i];

      for (std::vector<long>::size_type len = 1; len < nums.size(); len++)
      {
        for (std::vector<long>::size_type i = 1, j = 1+len; j <= nums.size(); i++, j++)
        {
          if (dp[i][j-1] < dp[i+1][j])
            dp[i][j] = nums[j-1] + std::min(dp[i][j-2], dp[i+1][j-1]);
          else
            dp[i][j] = nums[i-1] + std::min(dp[i+2][j], dp[i+1][j-1]);
        }
      }

      long sum = 0;
      for (std::vector<int>::size_type i = 0; i < nums.size(); i++)
        sum += nums[i];

      return dp[1][nums.size()] * 2 >= sum;
    }
};

int main()
{
  Solution s;
  assert(s.PredictTheWinner({1,5,2}) == false);
  assert(s.PredictTheWinner({1,5,233,7}) == true);
  return 0;
}
