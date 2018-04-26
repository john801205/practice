#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    bool PredictTheWinner(const std::vector<int> &nums)
    {
      std::vector<long> dp  (nums.size(), 0);

      for (std::vector<long>::size_type i = 0; i < nums.size(); i++)
        dp[i] = nums[i];

      for (std::vector<long>::size_type len = 1; len < nums.size(); len++)
        for (std::vector<long>::size_type i = 0, j = len; j < nums.size(); i++, j++)
          dp[i] = std::max(nums[j] - dp[i], nums[i] - dp[i+1]);

      return dp[0] >= 0;
    }
};

int main()
{
  Solution s;
  assert(s.PredictTheWinner({1,5,2}) == false);
  assert(s.PredictTheWinner({1,5,233,7}) == true);
  return 0;
}
