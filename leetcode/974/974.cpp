#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int subarraysDivByK(const std::vector<int> &A, int K)
    {
      std::vector<int> counts(K, 0);
      int zeroIndex = 0;
      int total = 0;

      for (auto num: A)
      {
        while (num >= K) num -= K;
        while (num < 0) num += K;

        if (zeroIndex < num) zeroIndex += K;
        zeroIndex -= num;
        counts[(zeroIndex+num) % K] += 1;
        total += counts[zeroIndex];
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
