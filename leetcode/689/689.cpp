#include <cassert>
#include <climits>
#include <iostream>
#include <vector>

class Solution
{
  public:
    std::vector<int> maxSumOfThreeSubarrays(const std::vector<int> &nums,
                                            const int               k)
    {
      const std::vector<int>::size_type N = nums.size();

      std::vector<std::vector<int>> dp    (4, std::vector<int> (N+1, 0));
      std::vector<std::vector<int>> index (4, std::vector<int> (N+1));
      std::vector<int>              accu  (N+1, 0);

      for (std::vector<int>::size_type i = 0; i < N; i++)
      {
        accu[i+1] = accu[i] + nums[i];
      }

      for (int i = 1; i < 4; i++)
      {
        for (std::vector<int>::size_type j = k*i; j <= N; j++)
        {
          int total = accu[j] - accu[j-k] + dp[i-1][j-k];

          if (total > dp[i][j-1])
          {
            dp[i][j] = total;
            index[i][j] = j-k;
          }
          else
          {
            dp[i][j] = dp[i][j-1];
            index[i][j] = index[i][j-1];
          }
        }
      }

      std::vector<int> result (3);
      result[2] = index[3][N];
      result[1] = index[2][result[2]];
      result[0] = index[1][result[1]];
      return result;
    }
};

int main(void)
{
  Solution s;
  assert(s.maxSumOfThreeSubarrays({1,2,1,2,6,7,5,1}, 2) == std::vector<int> ({0,3,5}));
  assert(s.maxSumOfThreeSubarrays({1,2,1,2,6,7,5,1}, 1) == std::vector<int> ({4,5,6}));
  assert(s.maxSumOfThreeSubarrays({1,2,1,2,6,7,5,1,7}, 2) == std::vector<int> ({3,5,7}));
  assert(s.maxSumOfThreeSubarrays({1,2,1,2,6,7,5,1,7}, 3) == std::vector<int> ({0,3,6}));
  assert(s.maxSumOfThreeSubarrays({1,2,1,2,6,7,5,1,7,9,4,1,2,7,6,5,3,2,1,9,4,2,3,1,2}, 3) == std::vector<int> ({4,8,13}));
  return 0;
}
