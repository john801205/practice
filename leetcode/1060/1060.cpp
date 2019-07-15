#include <vector>

class Solution {
  public:
    int missingElement(const std::vector<int>& nums, int k)
    {
      decltype(nums.size()) left = 0, right = nums.size();

      while (left < right)
      {
        const auto middle = left + (right - left) / 2;

        if (missing(nums, middle) >= k)
          right = middle;
        else
          left = middle+1;
      }

      return nums[left-1] + k - missing(nums, left-1);
    }

    int missing(const std::vector<int> &nums, int idx)
    {
      return nums[idx] - nums[0] - idx;
    }
};

int main()
{
  return 0;
}
