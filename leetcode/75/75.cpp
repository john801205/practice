#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    void sortColors(std::vector<int>& nums)
    {
      std::vector<int>::size_type zero = 0, two = nums.size();

      for (std::vector<int>::size_type i = 0; i < nums.size() && i < two; i++)
      {
        if (nums[i] == 0)
        {
          std::swap(nums[i], nums[zero]);
          zero++;
        }
        else if (nums[i] == 2)
        {
          two--;
          std::swap(nums[i], nums[two]);
          i--;
        }
      }
    }
};

int main()
{
  Solution s;
  std::vector<int> nums;

  nums = {2,0,2,1,1,0};
  s.sortColors(nums);
  assert(nums == std::vector<int> ({0,0,1,1,2,2}));

  nums = {2,0,2,0};
  s.sortColors(nums);
  assert(nums == std::vector<int> ({0,0,2,2}));

  nums = {0,1,1,0};
  s.sortColors(nums);
  assert(nums == std::vector<int> ({0,0,1,1}));

  nums = {2,2,1,1};
  s.sortColors(nums);
  assert(nums == std::vector<int> ({1,1,2,2}));

  return 0;
}
