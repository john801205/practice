#include <iostream>
#include <vector>

class Solution
{
  public:
    int maxArea(std::vector<int>& height)
    {
      if (height.size() == 0)
        return 0;

      std::vector<int>::size_type left = 0, right = height.size()-1;
      int max_water = 0;

      while (left < right)
      {
        int current_water = (right-left) * std::min(height[left], height[right]);
        max_water = std::max(max_water, current_water);

        if (height[left] < height[right])
        {
          left++;
        }
        else
        {
          right--;
        }
      }

      return max_water;
    }
};

int main(void)
{
  std::vector<int> height = {5, 8, 2, 1, 3, 1, 2, 1};
  Solution s;

  std::cout << s.maxArea(height) << '\n';

  return 0;
}
