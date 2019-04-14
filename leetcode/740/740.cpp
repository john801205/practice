#include <cassert>
#include <array>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int deleteAndEarn(const std::vector<int> &nums)
    {
      std::array<int, 10001> sums = {0};
      for (const auto &num: nums)
        sums[num] += num;

      int take = 0, skip = 0;
      for (int i = 1; i <= 10000; i++)
      {
        int takei = skip + sums[i];
        int skipi = std::max(take, skip);

        take = takei;
        skip = skipi;
      }

      return std::max(take, skip);
    }
};

int main()
{
  Solution s;
  assert(s.deleteAndEarn({1,8,5,9,6,9,4,1,7,3,3,6,3,3,8,2,6,3,2,2,1,2,9,8,7,1,1,10,6,7,3,9,6,10,5,4,10,1,6,7,4,7,4,1,9,5,1,5,7,5}) == 138);
  assert(s.deleteAndEarn({8,7,3,8,1,4,10,10,10,2}) == 52);
  assert(s.deleteAndEarn({}) == 0);
  assert(s.deleteAndEarn({3, 4, 2}) == 6);
  assert(s.deleteAndEarn({1, 1, 3, 4, 2}) == 6);
  assert(s.deleteAndEarn({1, 1, 3, 4, 2, 1}) == 7);
  assert(s.deleteAndEarn({2, 2, 3, 3, 3, 4}) == 9);
  return 0;
}
