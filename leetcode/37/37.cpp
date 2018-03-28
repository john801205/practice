#include <bitset>
#include <iostream>
#include <string>
#include <vector>

class Solution
{
  public:
    void solveSudoku(std::vector<std::vector<char>> &board)
    {
      solveSudokuDFS(board);
    }

    std::pair<std::vector<char>::size_type, std::vector<char>::size_type>
    fillUnique(std::vector<std::vector<char>> &board)
    {
      std::pair<std::vector<char>::size_type, std::vector<char>::size_type> indexes (9, 9);
      std::size_t min_possibilities = 9;
      bool changed = true;

      while (changed)
      {
        changed = false;

        for (std::vector<std::vector<char>>::size_type i = 0; i < board.size(); i++)
        {
          for (std::vector<char>::size_type j = 0; j < board[i].size(); j++)
          {
            if (board[i][j] != '.')
            {
              continue;
            }

            std::bitset<9> numbers = getAvailableNumbers(board, i, j);

            if (numbers.count() == 0)
            {
              return std::make_pair(i, j);
            }
            else if (numbers.count() != 1)
            {
              if (numbers.count() < min_possibilities)
              {
                indexes = std::make_pair(i, j);
                min_possibilities = numbers.count();
              }

              continue;
            }
            else
            {
              for (int k = 0; k < 9; k++)
              {
                if (numbers[k])
                {
                  changed = true;
                  board[i][j] = '1'+k;
                  break;
                }
              }
            }
          }
        }
      }

      return indexes;
    }

    bool solveSudokuDFS(std::vector<std::vector<char>> &board)
    {
      const std::vector<std::vector<char>> old = board;
      auto indexes = fillUnique(board);

      if (indexes.first == 9 && indexes.second == 9)
      {
        return true;
      }

      std::bitset<9> numbers = getAvailableNumbers(board, indexes.first, indexes.second);

      for (int k = 0; k < 9; k++)
      {
        if (numbers[k])
        {
          board[indexes.first][indexes.second] = '1' + k;

          if (solveSudokuDFS(board))
          {
            return true;
          }

          board[indexes.first][indexes.second] = '.';
        }
      }

      board = old;
      return false;
    }

    std::bitset<9> getAvailableNumbers(const std::vector<std::vector<char>> &board,
                                       const std::vector<char>::size_type    row,
                                       const std::vector<char>::size_type    col)
    {
      std::bitset<9> numbers;

      numbers.set();

      for (std::vector<char>::size_type i = 0; i < board[row].size(); i++)
      {
        if (i != col && board[row][i] != '.')
        {
          numbers.reset(board[row][i] - '1');
        }
      }

      for (std::vector<char>::size_type i = 0; i < board.size(); i++)
      {
        if (i != row && board[i][col] != '.')
        {
          numbers.reset(board[i][col] - '1');
        }
      }

      std::vector<char>::size_type box_row = row / 3 * 3, box_col = col / 3 * 3;
      for (std::vector<char>::size_type i = 0; i < 3; i++)
      {
        for (std::vector<char>::size_type j = 0; j < 3; j++)
        {
          if (box_row+i == row && box_col+j == col)
          {
            continue;
          }

          if (board[box_row+i][box_col+j] == '.')
          {
            continue;
          }

          numbers.reset(board[box_row+i][box_col+j] - '1');
        }
      }

      return numbers;
    }
};

int main(void)
{
  std::vector<std::vector<char>> board = {{'.','.','9','7','4','8','.','.','.'},{'7','.','.','.','.','.','.','.','.'},{'.','2','.','1','.','9','.','.','.'},{'.','.','7','.','.','.','2','4','.'},{'.','6','4','.','1','.','5','9','.'},{'.','9','8','.','.','.','3','.','.'},{'.','.','.','8','.','3','.','2','.'},{'.','.','.','.','.','.','.','.','6'},{'.','.','.','2','7','5','9','.','.'}};
  // std::vector<std::vector<char>> board = {{'.','.','.','2','.','.','.','6','3'},{'3','.','.','.','.','5','4','.','1'},{'.','.','1','.','.','3','9','8','.'},{'.','.','.','.','.','.','.','9','.'},{'.','.','.','5','3','8','.','.','.'},{'.','3','.','.','.','.','.','.','.'},{'.','2','6','3','.','.','5','.','.'},{'5','.','3','7','.','.','.','.','8'},{'4','7','.','.','.','1','.','.','.'}};
  Solution s;
  s.solveSudoku(board);
  return 0;
}
