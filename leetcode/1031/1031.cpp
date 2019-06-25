#include <cassert>
#include <climits>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int maxSumTwoNoOverlap(const std::vector<int> &A, int L, int M)
    {
      std::vector<int> prefix = A;
      for (std::vector<int>::size_type i = 1; i < prefix.size(); i++)
        prefix[i] = prefix[i-1] + prefix[i];

      int ans = 0, maxL = 0, maxR = 0;
      for (std::vector<int>::size_type i = L+M; i < prefix.size(); i++)
      {
        maxL = std::max(maxL, prefix[i-M] - prefix[i-M-L]);
        ans = std::max(ans, maxL + prefix[i] - prefix[i-M]);

        maxR = std::max(maxR, prefix[i-L] - prefix[i-L-M]);
        ans = std::max(ans, maxR + prefix[i] - prefix[i-L]);
      }

      return ans;
    }

};

int main()
{
  Solution s;
  assert(s.maxSumTwoNoOverlap({0,6,5,2,2,5,1,9,4}, 1, 2) == 20);
  assert(s.maxSumTwoNoOverlap({3,8,1,3,2,1,8,9,0}, 3, 2) == 29);
  assert(s.maxSumTwoNoOverlap({2,1,5,6,0,9,5,0,3,8}, 4, 3) == 31);
  return 0;
}
