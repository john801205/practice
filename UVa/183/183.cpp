#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
#include <string>

void transformB2D(const std::vector<std::vector<int>> &bit_maps,
                  int row_top, int row_bottom,
                  int col_left, int col_right,
                  int &p)
{
  // ignore 0x0 matrix
  if (row_top == row_bottom || col_left == col_right)
    return;

  int count = 0;
  for (int row = row_top; row < row_bottom; row++)
    for (int col = col_left; col < col_right; col++)
      count += bit_maps[row][col];

  if (p > 0 && p % 50 == 0)
    std::cout << '\n';
  p++;

  if (count == (row_bottom-row_top) * (col_right-col_left)) {
    std::cout << '1';
  } else if (count == 0) {
    std::cout << '0';
  } else {
    std::cout << 'D';
    int row_middle = (row_top+row_bottom+1) / 2,
        col_middle = (col_left+col_right+1) / 2;
    transformB2D(bit_maps, row_top, row_middle, col_left, col_middle, p);
    transformB2D(bit_maps, row_top, row_middle, col_middle, col_right, p);
    transformB2D(bit_maps, row_middle, row_bottom, col_left, col_middle, p);
    transformB2D(bit_maps, row_middle, row_bottom, col_middle, col_right, p);
  }
}

void transformD2B(std::vector<std::vector<char>> &bit_maps,
                  int row_top, int row_bottom,
                  int col_left, int col_right)
{
  if (row_top == row_bottom || col_left == col_right)
    return;

  char c = std::cin.get();
  if (c == '1' || c == '0') {
    for (int row = row_top; row < row_bottom; row++)
      for (int col = col_left; col < col_right; col++)
        bit_maps[row][col] = c;
  } else {
    int row_middle = (row_top+row_bottom+1) / 2,
        col_middle = (col_left+col_right+1) / 2;
    transformD2B(bit_maps, row_top, row_middle, col_left, col_middle);
    transformD2B(bit_maps, row_top, row_middle, col_middle, col_right);
    transformD2B(bit_maps, row_middle, row_bottom, col_left, col_middle);
    transformD2B(bit_maps, row_middle, row_bottom, col_middle, col_right);
  }
}

int main(void)
{
  char format;

  while (std::cin >> format) {
    if (format == '#')
      break;

    int rows, cols;
    std::cin >> rows >> cols;

    std::cout << (format == 'B'? 'D': 'B')
              << std::setw(4) << rows
              << std::setw(4) << cols
              << std::endl;

    if (format == 'B') {
      std::vector<std::vector<int>> bit_maps (rows, std::vector<int> (cols));
      std::string line;

      while (line.length() < unsigned(rows*cols)) {
        std::string temp;
        std::cin >> temp;
        line += temp;
      }

      for (int row = 0; row < rows; row++)
        for (int col = 0; col < cols; col++)
          bit_maps[row][col] = line[row*cols + col] - '0';

      int p = 0;
      transformB2D(bit_maps, 0, rows, 0, cols, p);
      std::cout << '\n';
    } else {
      std::vector<std::vector<char>> bit_maps (rows, std::vector<char> (cols));

      transformD2B(bit_maps, 0, rows, 0, cols);

      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          if (i+j > 0 && (i*cols+j) % 50 == 0)
            std::cout << '\n';
          std::cout << bit_maps[i][j];
        }
      }
      std::cout << '\n';
    }
  }

  return 0;
}
