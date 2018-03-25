#include <iostream>
#include <vector>

class Solution
{
  public:
    int search(const std::vector<int> &nums, const int target)
    {
      if (nums.size() == 0)
      {
        return -1;
      }

      std::vector<int>::size_type low = 0, high = nums.size() - 1;

      while (low < high)
      {
        std::vector<int>::size_type mid = low + (high - low) / 2;

        if (nums[mid] <= nums[high])
        {
          high = mid;
        }
        else
        {
          low = mid+1;
        }
      }

      high = (low + nums.size() - 1) % nums.size();

      if (target < nums[low] || target > nums[high])
        return -1;

      while (low != high)
      {
        auto mid = (low + (high + nums.size() - low) % nums.size() / 2) % nums.size();

        int val = nums[mid];

        if (val > target)
        {
          high = mid;
        }
        else if (val < target)
        {
          low = (mid + 1) % nums.size();
        }
        else
        {
          return mid;
        }
      }

      return nums[low] == target ? low : -1;
    }
};

int main(void)
{
  Solution s;
  std::vector<int> nums = {242,245,249,250,252,253,257,262,263,268,275,280,282,283,285,290,292,293,297,299,4,5,8,9,10,14,16,17,18,20,22,23,29,32,36,39,47,51,56,68,70,73,75,77,79,81,82,89,98,100,107,108,112,114,115,117,118,119,128,131,134,139,142,147,148,154,161,162,165,167,171,172,174,177,180,183,189,190,191,192,194,197,200,203,206,207,208,209,210,212,217,220,223,226,227,231,237};
  std::cout << s.search(nums, 54) << '\n';
  return 0;
}
