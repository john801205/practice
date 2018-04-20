#include <cassert>
#include <climits>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int maxProduct(const std::vector<int> &nums)
    {
      int maxProduct = nums[0];
      int minProduct = nums[0];
      int max = nums[0];

      for (std::vector<int>::size_type i = 1; i < nums.size(); i++)
      {
        if (nums[i] >= 0)
        {
          maxProduct = std::max(maxProduct * nums[i], nums[i]);
          minProduct = std::min(minProduct * nums[i], nums[i]);
        }
        else
        {
          int temp = maxProduct;
          maxProduct = std::max(minProduct * nums[i], nums[i]);
          minProduct = std::min(temp * nums[i], nums[i]);
        }

        max = std::max(max, maxProduct);
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
