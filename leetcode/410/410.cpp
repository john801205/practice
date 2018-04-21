#include <cassert>
#include <climits>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int splitArray(const std::vector<int> &nums, int m)
    {
      std::vector<std::vector<int>> dp (m, std::vector<int> (nums.size(), INT_MAX));

      std::vector<int> cumsums (nums.size()+1);

      for (std::vector<int>::size_type i = 0; i < nums.size(); i++)
        cumsums[i+1] = cumsums[i] + nums[i];

      for (std::vector<int>::size_type i = 0; i < nums.size(); i++)
        dp[0][i] = cumsums[i+1] - cumsums[0];

      for (int k = 1; k < m; k++)
        for (int i = k; i < nums.size(); i++)
          for (int j = i; j >= k; j--)
            dp[k][i] = std::min(dp[k][i], std::max(dp[k-1][j-1], cumsums[i+1] - cumsums[j]));

      return dp[m-1][nums.size()-1];
    }
};

int main()
{
  Solution s;
  assert(s.splitArray({7,2,5,10,8}, 2) == 18);
  assert(s.splitArray({7,2,5,10}, 3) == 10);
  assert(s.splitArray({7,2,5,10,8}, 3) == 14);
  return 0;
}
