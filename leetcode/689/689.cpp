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

      std::vector<std::vector<int>> dp (3, std::vector<int> (N, INT_MIN));
      std::vector<std::vector<std::vector<int>>> indexes (3, std::vector<std::vector<int>> (N));

      for (int subarray = 0; subarray < 3; subarray++)
      {
        int sum = 0;
        for (int i = 1; i <= k; i++)
        {
          sum += nums[N - k*subarray - i];
        }

        int total = sum + (subarray != 0 ? dp[subarray-1][N-k*subarray]: 0);
        dp[subarray][N - k*(subarray+1)] = total;
        indexes[subarray][N - k*(subarray+1)].emplace_back(N - k*(subarray+1));
        if (subarray != 0)
        {
          indexes[subarray][N-k*(subarray+1)].insert(std::end(indexes[subarray][N-k*(subarray+1)]),
                                                     std::begin(indexes[subarray-1][N-k*subarray]),
                                                     std::end(indexes[subarray-1][N-k*subarray]));
        }

        for (std::vector<int>::size_type i = nums.size() - k*(subarray+1); i-- > 0; )
        {
          sum += nums[i];
          sum -= nums[i+k];

          int total = sum + (subarray != 0 ? dp[subarray-1][i+k]: 0);

          if (total >= dp[subarray][i+1])
          {
            dp[subarray][i] = total;
            indexes[subarray][i].emplace_back(i);

            if (subarray != 0)
            {
              indexes[subarray][i].insert(std::end(indexes[subarray][i]),
                                          std::begin(indexes[subarray-1][i+k]),
                                          std::end(indexes[subarray-1][i+k]));
            }
          }
          else
          {
            dp[subarray][i] = dp[subarray][i+1];
            indexes[subarray][i] = indexes[subarray][i+1];
          }
        }

        // for (const auto &v: dp[subarray])
        // {
        //   std::cerr << v << ' ';
        // }
        // std::cerr << '\n';

        // for (const auto &v: indexes[subarray])
        // {
        //   bool first = true;
        //   for (const auto &vv: v)
        //   {
        //     if (!first)
        //       std::cerr << ',';

        //     std::cerr << vv;
        //     first = false;
        //   }
        //   std::cerr << ' ';
        // }
        // std::cerr << '\n';
      }

      return indexes.back().front();
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
