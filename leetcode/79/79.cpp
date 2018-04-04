#include <iostream>
#include <string>
#include <vector>

class Solution
{
  public:
    bool exist(const std::vector<std::vector<char>>& board, std::string word)
    {
      if (word.size() == 0 || board.size() == 0 || board[0].size() == 0)
      {
        return false;
      }

      std::vector<std::vector<bool>> used (board.size(), std::vector<bool> (board[0].size(), false));

      for (std::vector<char>::size_type i = 0; i < board.size(); i++)
      {
        for (std::vector<char>::size_type j = 0; j < board[i].size(); j++)
        {
          if (board[i][j] != word[0])
          {
            continue;
          }

          used[i][j] = true;

          if (dfs(board, i, j, used, word, 1))
          {
            return true;
          }

          used[i][j] = false;
        }
      }

      return false;
    }

    bool dfs(const std::vector<std::vector<char>> &board,
             const std::vector<char>::size_type    row,
             const std::vector<char>::size_type    col,
                   std::vector<std::vector<bool>> &used,
             const std::string                    &word,
             const std::string::size_type          index)
    {
      if (index == word.size())
      {
        return true;
      }

      std::vector<std::vector<int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

      for (const auto &dir: dirs)
      {
        auto x = row + dir[0], y = col + dir[1];

        if (x >= board.size() || y >= board[x].size() || word[index] != board[x][y] || used[x][y])
        {
          continue;
        }

        used[x][y] = true;

        if (dfs(board, x, y, used, word, index+1))
        {
          return true;
        }

        used[x][y] = false;
      }

      return false;
    }
};

int main(void)
{
  return 0;
}
