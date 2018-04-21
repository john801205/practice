#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    double largestSumOfAverages(const std::vector<int> &A, const int K)
    {
      std::vector<std::vector<double>> dp (K, std::vector<double> (A.size(), 0));

      double sum = 0;
      for (std::vector<double>::size_type i = 0; i < dp[0].size(); i++)
      {
        sum += A[i];
        dp[0][i] = sum / (i+1);
      }

      for (int i = 1; i < K; i++)
      {
        for (std::vector<double>::size_type j = i; j < dp[i].size(); j++)
        {
          double sum = 0;

          for (std::vector<double>::size_type k = j; k >= i; k--)
          {
            sum += A[k];
            dp[i][j] = std::max(dp[i][j], sum / (j-k+1) + dp[i-1][k-1]);
          }
        }
      }

      return dp.back().back();
    }
};

int main()
{
  Solution s;
  assert(s.largestSumOfAverages({3}, 1) == 3);
  assert(s.largestSumOfAverages({3,2}, 1) == 2.5);
  assert(s.largestSumOfAverages({3,2}, 2) == 5);
  assert(s.largestSumOfAverages({9,1,2,3,9}, 3) == 20);
  return 0;
}
