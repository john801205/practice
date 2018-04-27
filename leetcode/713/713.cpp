#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int numSubarrayProductLessThanK(const std::vector<int> &nums, int k)
    {
      long long product = 1;
      int result = 0;

      for (std::vector<int>::size_type left = 0, right = 0; right < nums.size(); right++)
      {
        product *= nums[right];

        while (product >= k && left <= right)
        {
          product /= nums[left];
          left++;
        }

        result += right-left+1;
      }

      return result;
    }
};

int main()
{
  Solution s;
  assert(s.numSubarrayProductLessThanK({10,5,2,6}, 100) == 8);
  assert(s.numSubarrayProductLessThanK({10,5,2,6,1}, 1) == 0);
  assert(s.numSubarrayProductLessThanK({1,2,3}, 0) == 0);
  return 0;
}
