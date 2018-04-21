#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    double largestSumOfAverages(const std::vector<int> &A, const int K)
    {
      std::vector<double> dp (A.size(), 0);

      double sum = 0;
      for (std::vector<double>::size_type i = 0; i < dp.size(); i++)
      {
        sum += A[i];
        dp[i] = sum / (i+1);
      }

      for (int i = 1; i < K; i++)
      {
        for (std::vector<double>::size_type j = dp.size(); j-- > i; )
        {
          double sum = 0;

          for (std::vector<double>::size_type k = j; k >= i; k--)
          {
            sum += A[k];
            dp[j] = std::max(dp[j], sum / (j-k+1) + dp[k-1]);
          }
        }
      }

      return dp.back();
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
