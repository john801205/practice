#include <iostream>
#include <vector>

class Solution
{
  public:
    int firstMissingPositive(std::vector<int> &nums)
    {
      const int n = nums.size();

      for (std::vector<int>::size_type i = 0; i < nums.size(); i++)
      {
        while (nums[i] > 0 && nums[i] <= n && nums[nums[i]-1] != nums[i])
        {
          std::swap(nums[i], nums[nums[i]-1]);
        }
      }

      int i;
      for (i = 0; i < n; i++)
      {
        if (nums[i] != i+1)
        {
          return i+1;
        }
      }

      return i+1;
    }
};

int main(void)
{
  Solution s;
  std::vector<int> nums = {1, 2, 3, 4, 5};
  std::cout << s.firstMissingPositive(nums) << '\n';
  return 0;
}
