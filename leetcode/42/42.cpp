#include <algorithm>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int trap(std::vector<int>& height)
    {
      if (height.size() == 0)
        return 0;

      std::vector<int> left_max(height), right_max(height);

      for (std::vector<int>::size_type i = 1; i < left_max.size(); i++)
        left_max[i] = std::max(left_max[i], left_max[i-1]);

      for (std::vector<int>::size_type i = right_max.size()-1; i-- > 0; )
        right_max[i] = std::max(right_max[i], right_max[i+1]);

      int water = 0;
      for (std::vector<int>::size_type i = 0; i < height.size(); i++)
        water += std::min(left_max[i], right_max[i]) - height[i];

      return water;
    }
};

int main(void)
{
  std::vector<int> height = {7, 2, 3, 4, 5 ,6,7};
  std::cout << Solution().trap(height) << '\n';
}
