#include <cassert>
#include <iostream>
#include <string>
#include <vector>

class Solution
{
  public:
    std::vector<std::vector<std::string>> solveNQueens(int n)
    {
      std::vector<std::vector<std::string>> result;
      std::vector<int> pos (n);

      std::vector<bool> rows (n, true);
      std::vector<bool> cols (n, true);
      std::vector<bool> left_diagonals (2*n-1, true);
      std::vector<bool> right_diagonals (2*n-1, true);

      dfs(pos, 0, n, rows, cols, left_diagonals, right_diagonals, result);

      return result;
    }

    void dfs(std::vector<int>  &pos,
             const int          row,
             const int          n,
             std::vector<bool> &rows,
             std::vector<bool> &cols,
             std::vector<bool> &left_diagonals,
             std::vector<bool> &right_diagonals,
             std::vector<std::vector<std::string>> &result)
    {
      if (row == n)
      {
        std::vector<std::string> board (n, std::string (n, '.'));

        for (int i = 0; i < n; i++)
        {
          board[i][pos[i]] = 'Q';
        }

        result.emplace_back(board);

        return;
      }

      for (int col = 0; col < n; col++)
      {
        if (rows[row]
            && cols[col]
            && left_diagonals[row+col]
            && right_diagonals[col-row+n-1])
        {
          pos[row] = col;

          rows[row] = false;
          cols[col] = false;
          left_diagonals[row+col] = false;
          right_diagonals[col-row+n-1] = false;

          dfs(pos, row+1, n, rows, cols, left_diagonals, right_diagonals, result);

          rows[row] = true;
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
  assert(s.solveNQueens(1) == std::vector<std::vector<std::string>> ({{"Q"}}));
  assert(s.solveNQueens(2) == std::vector<std::vector<std::string>> ({}));
  assert(s.solveNQueens(3) == std::vector<std::vector<std::string>> ({}));
  assert(s.solveNQueens(4) == std::vector<std::vector<std::string>> ({{".Q..","...Q","Q...","..Q."},{"..Q.","Q...","...Q",".Q.."}}));
  assert(s.solveNQueens(5) == std::vector<std::vector<std::string>> ({{"Q....","..Q..","....Q",".Q...","...Q."},{"Q....","...Q.",".Q...","....Q","..Q.."},{".Q...","...Q.","Q....","..Q..","....Q"},{".Q...","....Q","..Q..","Q....","...Q."},{"..Q..","Q....","...Q.",".Q...","....Q"},{"..Q..","....Q",".Q...","...Q.","Q...."},{"...Q.","Q....","..Q..","....Q",".Q..."},{"...Q.",".Q...","....Q","..Q..","Q...."},{"....Q",".Q...","...Q.","Q....","..Q.."},{"....Q","..Q..","Q....","...Q.",".Q..."}}));
  return 0;
}
