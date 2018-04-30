#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>

class Solution
{
  public:
    void nextPermutation(std::vector<int>& nums)
    {
      int i = nums.size() - 2;

      while (i >= 0 && nums[i] >= nums[i+1])
        i--;

      if (i >= 0)
      {
        int j = nums.size() - 1;
        while (nums[j] <= nums[i])
          j--;

        std::swap(nums[i], nums[j]);
      }

      std::reverse(std::begin(nums)+i+1, std::end(nums));
    }
};

int main()
{
  Solution s;

  std::vector<int> nums ({1,2,3});
  s.nextPermutation(nums);
  assert(nums == std::vector<int> ({1,3,2}));
  s.nextPermutation(nums);
  assert(nums == std::vector<int> ({2,1,3}));
  s.nextPermutation(nums);
  assert(nums == std::vector<int> ({2,3,1}));

  nums = {3,2,1};
  s.nextPermutation(nums);
  assert(nums == std::vector<int> ({1,2,3}));

  nums = {1,1,5};
  s.nextPermutation(nums);
  assert(nums == std::vector<int> ({1,5,1}));
  s.nextPermutation(nums);
  assert(nums == std::vector<int> ({5,1,1}));

  return 0;
}
