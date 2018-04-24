#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

class Solution
{
  public:
    int numberOfArithmeticSlices(const std::vector<int> &A)
    {
      std::vector<std::unordered_map<long, int>> dp (A.size());
      int sum = 0;

      for (std::vector<int>::size_type i = 1; i < A.size(); i++)
      {
        for (std::vector<int>::size_type j = 0; j < i; j++)
        {
          long diff = A[i];
          diff -= A[j];

          int result = 0;
          if (dp[j].find(diff) != dp[j].end())
            result = dp[j][diff];

          dp[i][diff] += result + 1;
          sum += result;
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
