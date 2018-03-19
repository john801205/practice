#include <cmath>

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

class Solution {
  public:
    std::vector<int> findDisappearedNumbers(std::vector<int>& nums)
    {
      std::vector<int> result;

      for (const auto &num: nums)
      {
        auto v = std::abs(num);

        if (nums[v-1] > 0)
        {
          nums[v-1] = -nums[v-1];
        }
      }

      for (std::vector<int>::size_type i = 0; i < nums.size(); i++)
      {
        if (nums[i] > 0)
        {
          result.push_back(i+1);
        }
      }

      return result;
    }
};

int main(void)
{
  return 0;
}
