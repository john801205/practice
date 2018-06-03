#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    bool searchMatrix(const std::vector<std::vector<int>> &matrix, int target)
    {
      if (matrix.size() == 0 || matrix[0].size() == 0)
        return false;

      int m = matrix.size(), n = matrix[0].size();
      int row = 0, col = n-1;

      while (row < m && col >= 0)
      {
        int num = matrix[row][col];

        if (num == target)
          return true;
        else if (num > target)
          col--;
        else
          row++;
      }

      return false;
    }
};

int main()
{
  Solution s;
  assert(s.searchMatrix({{1,   4,  7, 11, 15}, {2,   5,  8, 12, 19}, {3,   6,  9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}}, 5) == true);
  assert(s.searchMatrix({{1,   4,  7, 11, 15}, {2,   5,  8, 12, 19}, {3,   6,  9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}}, 20) == false);
  return 0;
}
