#include <cassert>
#include <iostream>
#include <string>
#include <vector>

class Solution
{
  public:
    int totalNQueens(int n)
    {
      int result = 0;

      std::vector<bool> cols (n, true);
      std::vector<bool> left_diagonals (2*n-1, true);
      std::vector<bool> right_diagonals (2*n-1, true);

      dfs(0, n, cols, left_diagonals, right_diagonals, result);

      return result;
    }

    void dfs(const int          row,
             const int          n,
             std::vector<bool> &cols,
             std::vector<bool> &left_diagonals,
             std::vector<bool> &right_diagonals,
             int               &result)
    {
      if (row == n)
      {
        result++;
        return;
      }

      for (int col = 0; col < n; col++)
      {
        if (cols[col]
            && left_diagonals[row+col]
            && right_diagonals[col-row+n-1])
        {
          cols[col] = false;
          left_diagonals[row+col] = false;
          right_diagonals[col-row+n-1] = false;

          dfs(row+1, n, cols, left_diagonals, right_diagonals, result);

          cols[col] = true;
          left_diagonals[row+col] = true;
          right_diagonals[col-row+n-1] = true;
        }
      }
    }
};

int main(void)
{
  Solution s;
  assert(s.totalNQueens(1) ==  1);
  assert(s.totalNQueens(2) ==  0);
  assert(s.totalNQueens(3) ==  0);
  assert(s.totalNQueens(4) ==  2);
  assert(s.totalNQueens(5) == 10);
  return 0;
}
