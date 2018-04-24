#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

class Solution
{
  public:
    int numberOfArithmeticSlices(const std::vector<int> &A)
    {
      std::vector<std::unordered_map<std::vector<int>::size_type, int>> dp (A.size());
      int sum = 0;

      for (std::vector<int>::size_type i = 2; i < A.size(); i++)
      {
        for (std::vector<int>::size_type j = 0; j < i; j++)
        {
          for (const auto &pair: dp[j])
          {
            long diff = A[i], diff2 = A[j];
            diff -= A[j];
            diff2 -= A[pair.first];

            if (diff == diff2)
            {
              dp[i][j] += pair.second;
              sum += pair.second;
            }
          }
        }

        for (std::vector<int>::size_type j = 0; j+1 < i; j++)
        {
          for (std::vector<int>::size_type k = j+1; k < i; k++)
          {
            long diff = A[i], diff2 = A[k];
            diff -= A[k];
            diff2 -= A[j];
            if (diff == diff2)
            {
              dp[i][k] += 1;
              sum += 1;
            }
          }
        }
      }

      return sum;
    }
};

int main()
{
  Solution s;
  assert(s.numberOfArithmeticSlices({2,4,6,8,10}) == 7);
  assert(s.numberOfArithmeticSlices({0,2000000000,-294967296}) == 0);
  return 0;
}
