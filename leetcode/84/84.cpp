#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

class Solution
{
  public:
    int largestRectangleArea(const std::vector<int> &heights)
    {
      if (!heights.empty() && heights.front() < heights.back())
      {
        std::vector<int> copy = heights;
        std::reverse(std::begin(copy), std::end(copy));
        return largestRectangleArea(copy);
      }

      std::cerr << "heights: ";
      for (const auto &height: heights)
        std::cerr << height << ' ';
      std::cerr << '\n';

      std::vector<std::pair<int, int>> stack;
      int largest = 0;

      for (int i = 0; i < heights.size(); i++)
      {
        int index = i;
        int current = heights[i];

        while (!stack.empty())
        {
          int height = stack.back().second;

          if (heights[i] > height)
          {
            break;
          }

          index = stack.back().first;
          current = std::max(current, heights[i] * (i-index+1));
          stack.pop_back();
        }

        for (const auto &rec: stack)
        {
          current = std::max(current, rec.second * (i-rec.first+1));
        }

        largest = std::max(largest, current);
        stack.emplace_back(std::make_pair(index, heights[i]));

        std::cerr << "stack: ";
        for (const auto &rec: stack)
          std::cerr << '(' << rec.first << ", " << rec.second << ") ";
        std::cerr << '\n';

        std::cerr << "largest: " << largest << ", current: " << current << '\n';
      }

      return largest;
    }
};

int main(void)
{
  Solution s;

  // std::cout << s.largestRectangleArea({0, 1,2,3,4,5,6,7,8,9}) << '\n';
  // std::cout << s.largestRectangleArea({2, 1, 5, 6, 2, 3}) << '\n';
  std::cout << s.largestRectangleArea({0, 1,2,3,4,5,6,7,8,9, 7, 2, 3, 4, 1, 5, 0, 9, 10, 21, 3}) << '\n';

  return 0;
}
