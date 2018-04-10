#include <iostream>
#include <vector>

class Solution
{
  public:
    int findTargetSumWays(std::vector<int> &nums, int S)
    {
      if (nums.size() == 0)
      {
        return 0;
      }

      if (nums.size() == 1)
      {
        if (nums[0] == S && nums[0] == -S)
          return 2;
        else if (nums[0] == S || nums[0] == -S)
          return 1;
        else
          return 0;
      }

      const int value = nums.back();
      nums.pop_back();

      const int result = findTargetSumWays(nums, S+value)
                         + findTargetSumWays(nums, S-value);
      nums.emplace_back(value);

      return result;
    }
};

int main(void)
{
  Solution s;
  std::vector<int> nums = {1,1,1,1,1};
  std::cout << s.findTargetSumWays(nums, 3) << '\n';
  return 0;
}
