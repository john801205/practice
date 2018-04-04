#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int singleNumber(const std::vector<int>& nums)
    {
      int once = 0, twice = 0;

      for (const auto &num: nums)
      {
        once = (once ^ num) & (~twice);
        twice = (twice ^ num) & (~once);
      }

      return once;
    }
};

int main(void)
{
  Solution s;
  assert(s.singleNumber({1}) == 1);
  assert(s.singleNumber({1, 3, 3, 3}) == 1);
  assert(s.singleNumber({1, 5, 3, 3, 3, 5, 5}) == 1);
  assert(s.singleNumber({1, 2, 5, 2, 3, 3, 3, 2, 5, 5}) == 1);
  return 0;
}
