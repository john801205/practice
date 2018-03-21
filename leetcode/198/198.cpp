#include <algorithm>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int rob(std::vector<int> &nums)
    {
      int pre = 0, cur = 0;

      for (const auto &num: nums)
      {
        int temp = std::max(pre+num, cur);
        pre = cur;
        cur = temp;
      }

      return std::max(pre, cur);
    }
};

int main(void)
{
  Solution s;
  std::vector<int> nums = {5, 1, 2, 100, 99};

  std::cerr << s.rob(nums) << '\n';

  return 0;
}
