#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int subarraysDivByK(const std::vector<int> &A, int K)
    {
      std::vector<int> counts(K, 0);
      int prefix = 0, total = 0;
      counts[0] = 1;

      for (const auto &num: A)
      {
        prefix = (prefix + num % K + K) % K;
        total += counts[prefix];
        counts[prefix] += 1;
      }

      return total;
    }
};

int main()
{
  Solution s;
  assert(s.subarraysDivByK({4,5,0,-2,-3,1}, 5) == 7);
  return 0;
}
