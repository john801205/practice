#include <iostream>
#include <vector>

class Solution
{
  public:
    void solve(std::vector<std::vector<char>> &board)
    {
      if (board.size() == 0 || board[0].size() == 0)
        return;

      std::vector<std::vector<bool>> visited (board.size(), std::vector<bool> (board[0].size(), false));

      for (std::vector<char>::size_type i = 0; i < board.size(); i++)
      {
        dfs(board, visited, i, 0);
        dfs(board, visited, i, board[i].size()-1);
      }

      for (std::vector<char>::size_type j = 0; j < board[0].size(); j++)
      {
        dfs(board, visited, 0, j);
        dfs(board, visited, board.size()-1, j);
      }

      for (std::vector<char>::size_type i = 0; i < board.size(); i++)
      {
        for (std::vector<char>::size_type j = 0; j < board[i].size(); j++)
        {
          if (!visited[i][j])
          {
            board[i][j] = 'X';
          }
        }
      }
    }

    void dfs(std::vector<std::vector<char>> &board,
             std::vector<std::vector<bool>> &visited,
             std::vector<char>::size_type    row,
             std::vector<char>::size_type    col)
    {
      if (row >= board.size() || col >= board[row].size())
        return;

      if (visited[row][col] || board[row][col] == 'X')
        return;

      visited[row][col] = true;
      dfs(board, visited, row-1, col);
      dfs(board, visited, row+1, col);
      dfs(board, visited, row, col-1);
      dfs(board, visited, row, col+1);
    }
};

int main(void)
{
  return 0;
}
