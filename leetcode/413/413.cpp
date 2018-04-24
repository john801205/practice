#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int numberOfArithmeticSlices(const std::vector<int> &A)
    {
      int sum = 0;
      std::vector<int> dp (A.size(), 0);

      for (std::vector<int>::size_type i = 2; i < A.size(); i++)
      {
        if (A[i] - A[i-1] == A[i-1] - A[i-2])
        {
          dp[i] = dp[i-1] + 1;
        }

        sum += dp[i];
      }

      return sum;
    }
};

int main()
{
  Solution s;
  assert(s.numberOfArithmeticSlices({1,2,3,4}) == 3);
  assert(s.numberOfArithmeticSlices({1,2,3,4,5}) == 6);
  assert(s.numberOfArithmeticSlices({1,2,3,4,5,1,3,5,7,9,11}) == 16);
  return 0;
}
