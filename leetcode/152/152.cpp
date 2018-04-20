#include <cassert>
#include <climits>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int maxProduct(const std::vector<int> &nums)
    {
      int maxPositive = 0, minNegative = 0;
      int max = INT_MIN;

      for (std::vector<int>::size_type i = 0; i < nums.size(); i++)
      {
        if (nums[i] < 0)
        {
          if (maxPositive != 0 && minNegative != 0)
          {
            int temp = maxPositive;
            maxPositive = minNegative * nums[i];
            minNegative = temp * nums[i];
            max = std::max(max, maxPositive);
          }
          else if (maxPositive != 0)
          {
            minNegative = maxPositive * nums[i];
            maxPositive = 0;
            max = std::max(max, minNegative);
          }
          else if (minNegative != 0)
          {
            maxPositive = minNegative * nums[i];
            minNegative = nums[i];
            max = std::max(max, maxPositive);
          }
          else
          {
            minNegative = nums[i];
            max = std::max(max, minNegative);
          }
        }
        else if (nums[i] > 0)
        {
          if (maxPositive != 0)
            maxPositive = maxPositive * nums[i];
          else
            maxPositive = nums[i];

          if (minNegative != 0)
            minNegative = minNegative * nums[i];

          max = std::max(max, maxPositive);
        }
        else
        {
          maxPositive = 0;
          minNegative = 0;
          max = std::max(max, 0);
        }
      }

      return max;
    }
};

int main()
{
  Solution s;
  assert(s.maxProduct({2,3,-2,4}) == 6);
  assert(s.maxProduct({-2,0,-1}) == 0);
  assert(s.maxProduct({-2}) == -2);
  assert(s.maxProduct({2,-5,-2,-4,3}) == 24);
  assert(s.maxProduct({1,2,-1,-2,2,1,-2,1,4,-5,4}) == 1280);
  return 0;
}
