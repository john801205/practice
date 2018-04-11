#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int longestIncreasingPath(const std::vector<std::vector<int>> &matrix)
    {
      std::vector<std::vector<int>> cache = matrix;
      for (auto &row: cache)
      {
        for (auto &v: row)
        {
          v = 0;
        }
      }

      int length = 0;

      for (std::vector<int>::size_type i = 0; i < matrix.size(); i++)
      {
        for (std::vector<int>::size_type j = 0; j < matrix[i].size(); j++)
        {
          length = std::max(length, dfs(matrix, i, j, cache));
        }
      }

      return length;
    }

    int dfs(const std::vector<std::vector<int>> &matrix,
            const std::vector<int>::size_type    row,
            const std::vector<int>::size_type    col,
                  std::vector<std::vector<int>> &cache)
    {
      if (cache[row][col] != 0)
      {
        return cache[row][col];
      }

      int length = 0;

      if (row > 0 && col < matrix[row-1].size() && matrix[row][col] > matrix[row-1][col])
      {
        length = std::max(length, dfs(matrix, row-1, col, cache));
      }

      if (row+1 < matrix.size() && col < matrix[row+1].size() && matrix[row][col] > matrix[row+1][col])
      {
        length = std::max(length, dfs(matrix, row+1, col, cache));
      }

      if (col > 0 && matrix[row][col] > matrix[row][col-1])
      {
        length = std::max(length, dfs(matrix, row, col-1, cache));
      }

      if (col+1 < matrix[row].size() && matrix[row][col] > matrix[row][col+1])
      {
        length = std::max(length, dfs(matrix, row, col+1, cache));
      }

      cache[row][col] = length+1;
      return length+1;
    }
};

int main(void)
{
  Solution s;

  assert(s.longestIncreasingPath({}) == 0);
  assert(s.longestIncreasingPath({{}}) == 0);
  assert(s.longestIncreasingPath({{9,9,4},{6,6,8},{2,1,1}}) == 4);
  assert(s.longestIncreasingPath({{3,4,5},{3,2,6},{2,2,1}}) == 4);
  assert(s.longestIncreasingPath({{1,2,3},{4,5,6},{7,8,9}}) == 5);

  return 0;
}
