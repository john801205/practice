#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int rob(const std::vector<int> &nums)
    {
      if (nums.size() == 0)
        return 0;
      else if (nums.size() == 1)
        return nums[0];

      return std::max(rob(nums, 0, nums.size()-2), rob(nums, 1, nums.size()-1));
    }

    int rob(const std::vector<int> &nums,
                  std::vector<int>::size_type low,
                  std::vector<int>::size_type high)
    {
      int include = 0, exclude = 0;

      for (std::vector<int>::size_type i = low; i <= high; i++)
      {
        int temp = include;
        include = exclude + nums[i];
        exclude = std::max(temp, exclude);
      }

      return include;
    }
};

int main()
{
  Solution s;
  assert(s.rob({2}) == 2);
  assert(s.rob({2,3}) == 3);
  assert(s.rob({2,3,2}) == 3);
  assert(s.rob({1,2,3,1}) == 4);
  return 0;
}
