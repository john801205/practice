#include <iostream>
#include <stack>
#include <vector>

class Solution
{
  public:
    int largestRectangleArea(std::vector<int> &heights)
    {
      std::stack<std::vector<int>::size_type> stack;
      int largest = 0;

      // We append a 0 at the end of heights to make sure every non-zero
      // element will be popped during the for loop
      heights.push_back(0);

      for (std::vector<int>::size_type i = 0; i < heights.size(); i++)
      {
        while (!stack.empty() && heights[i] <= heights[stack.top()])
        {
          std::vector<int>::size_type index = stack.top();
          stack.pop();

          int current = heights[index] * (stack.empty() ? i : i-stack.top()-1);

          largest = std::max(largest, current);
        }

        stack.push(i);
      }

      return largest;
    }
};

int main(void)
{
  Solution s;
  // std::vector<int> heights = {0, 1,2,3,4,5,6,7,8,9, 7, 2, 3, 4, 1, 5, 0, 9, 10, 21, 3};
  // std::vector<int> heights = {2, 1, 5, 6, 2, 3};
  std::vector<int> heights = {0, 1,2,3,4,5,6,7,8,9};

  std::cout << s.largestRectangleArea(heights) << '\n';

  return 0;
}
