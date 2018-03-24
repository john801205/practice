#include <algorithm>
#include <iostream>
#include <vector>

class Solution
{
  public:
    std::vector<std::vector<int>> threeSum(std::vector<int> &nums)
    {
      std::vector<std::vector<int>> results;

      std::sort(std::begin(nums), std::end(nums));

      for (std::vector<int>::size_type i = 0; i < nums.size(); i++)
      {
        int target = -nums[i];
        std::vector<int>::size_type left = i+1, right = nums.size()-1;

        while (left < right)
        {
          int value = nums[left] + nums[right];

          if (value > target)
          {
            right--;
          }
          else if (value < target)
          {
            left++;
          }
          else
          {
            std::vector<int> triplet = {nums[i], nums[left], nums[right]};
            results.emplace_back(triplet);
            left++;
            right--;

            // skip duplicates of second number
            while (left < right && nums[left] == nums[left-1])
            {
              left++;
            }

            // skip duplicates of third number
            while (right > left && nums[right] == nums[right+1])
            {
              right--;
            }
          }
        }

        // skip duplicates of first number
        while (i+1 < nums.size() && nums[i+1] == nums[i])
        {
          i++;
        }
      }

      return results;
    }
};

int main(void)
{
  Solution s;
  std::vector<int> nums = {-1,0,1,2,-1,-4};
  s.threeSum(nums);
  return 0;
}
