#include <iostream>
#include <vector>

class Solution
{
  public:
    int maximalRectangle(const std::vector<std::vector<char>> &matrix)
    {
      if (matrix.size() == 0 || matrix[0].size() == 0)
      {
        return 0;
      }

      std::vector<std::vector<int>> tops  (matrix.size(), std::vector<int> (matrix[0].size(), 0));
      std::vector<std::vector<int>> lefts (matrix.size(), std::vector<int> (matrix[0].size(), 0));
      std::vector<std::vector<int>> cols  (matrix.size(), std::vector<int> (matrix[0].size(), 0));
      std::vector<std::vector<int>> rows  (matrix.size(), std::vector<int> (matrix[0].size(), 0));
      int max_area = 0;

      for (std::vector<std::vector<char>>::size_type i = 0; i < matrix.size(); i++)
      {
        for (std::vector<char>::size_type j = 0; j < matrix[i].size(); j++)
        {
          if (matrix[i][j] == '0')
          {
            continue;
          }

          int area = 1;
          tops[i][j] = 1;
          lefts[i][j] = 1;
          cols[i][j] = 1;
          rows[i][j] = 1;

          if (j > 0 && matrix[i][j-1] == '1')
          {
            rows[i][j] += rows[i][j-1];

            if (rows[i][j] > area)
            {
              area = rows[i][j];
              tops[i][j] = 1;
              lefts[i][j] = rows[i][j];
            }
          }

          if (i > 0 && matrix[i-1][j] == '1')
          {
            cols[i][j] += cols[i-1][j];

            if (cols[i][j] > area)
            {
              area = cols[i][j];
              tops[i][j] = cols[i][j];
              lefts[i][j] = 1;
            }
          }

          if (i > 0 && j > 0 && matrix[i-1][j-1] == '1' && matrix[i-1][j] == '1' && matrix[i][j-1] == '1')
          {
            int left = std::min(lefts[i-1][j-1], rows[i][j-1]) + 1;
            int top  = std::min(tops[i-1][j-1], cols[i-1][j]) + 1;

            if (left * top > area)
            {
              area = left * top;
              tops[i][j] = top;
              lefts[i][j] = left;
            }
          }

          max_area = std::max(max_area, area);
        }
      }

      return max_area;
    }
};

int main(void)
{
  return 0;
}
