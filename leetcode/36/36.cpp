#include <iostream>
#include <bitset>
#include <vector>

class Solution
{
  public:
    bool isValidSudoku(std::vector<std::vector<char>> &board)
    {
      std::vector<std::bitset<9>> used_row(9), used_col(9), used_subbox(9);

      for (std::vector<std::vector<char>>::size_type i = 0; i < board.size(); i++)
      {
        for (std::vector<char>::size_type j = 0; j < board[i].size(); j++)
        {
          if (board[i][j] == '.')
          {
            continue;
          }

          int v = board[i][j] - '1';
          int k = i / 3 * 3 + j / 3;

          if (used_row[i][v] || used_col[j][v] || used_subbox[k][v])
          {
            return false;
          }

          used_row[i].set(v);
          used_col[j].set(v);
          used_subbox[k].set(v);
        }
      }

      return true;
    }
};

int main(void)
{
  return 0;
}
