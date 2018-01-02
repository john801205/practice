#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
#include <string>

std::string transformB2D(const std::vector<std::vector<bool>> &bit_maps,
                         int row_top, int row_bottom,
                         int col_left, int col_right)
{
  if (row_top == row_bottom && col_left == col_right)
    return bit_maps[row_top][col_left] ? "1": "0";

  bool equal = true, previous = bit_maps[row_top][col_left];
  for (int row = row_top; row < row_bottom && equal; row++)
    for (int col = col_left; col < col_right && equal; col++)
      if (bit_maps[row][col] != previous)
        equal = false;

  if (equal)
    return previous ? "1": "0";

  std::string result ("D");
  result += transformB2D(bit_maps, row_top, (row_top+row_bottom+1)/2, col_left, (col_left+col_right+1)/2);
  if ((col_left+col_right+1)/2 < col_right)
    result += transformB2D(bit_maps, row_top, (row_top+row_bottom+1)/2, (col_left+col_right+1)/2, col_right);
  if ((row_top+row_bottom+1)/2 < row_bottom)
    result += transformB2D(bit_maps, (row_top+row_bottom+1)/2, row_bottom, col_left, (col_left+col_right+1)/2);
  if ((row_top+row_bottom+1)/2 < row_bottom && (col_left+col_right+1)/2 < col_right)
    result += transformB2D(bit_maps, (row_top+row_bottom+1)/2, row_bottom, (col_left+col_right+1)/2, col_right);

  return result;
}

void transformD2B(std::vector<std::vector<char>> &bit_maps,
                  std::queue<char> &queue,
                  int row_top, int row_bottom,
                  int col_left, int col_right)
{
  if (queue.empty()) {
    std::string line;
    std::cin >> line;
    for (auto &c: line)
      queue.push(c);
  }

  char c = queue.front();
  queue.pop();

  if (c == '1' || c == '0') {
    for (int row = row_top; row < row_bottom; row++)
      for (int col = col_left; col < col_right; col++)
        bit_maps[row][col] = c;
  } else {
    transformD2B(bit_maps, queue, row_top, (row_top+row_bottom+1)/2, col_left, (col_left+col_right+1)/2);
    if ((col_left+col_right+1)/2 < col_right)
      transformD2B(bit_maps, queue, row_top, (row_top+row_bottom+1)/2, (col_left+col_right+1)/2, col_right);
    if ((row_top+row_bottom+1)/2 < row_bottom)
      transformD2B(bit_maps, queue, (row_top+row_bottom+1)/2, row_bottom, col_left, (col_left+col_right+1)/2);
    if ((row_top+row_bottom+1)/2 < row_bottom && (col_left+col_right+1)/2 < col_right)
      transformD2B(bit_maps, queue, (row_top+row_bottom+1)/2, row_bottom, (col_left+col_right+1)/2, col_right);
  }
}

int main(void)
{
  std::string format;

  while (std::cin >> format) {
    if (format == "#")
      break;

    int rows, cols;
    std::cin >> rows >> cols;

    if (format == "B") {
      std::vector<std::vector<bool>> bit_maps (rows, std::vector<bool> (cols));
      for (int i = 0; i < rows*cols; ) {
        std::string line;
        std::cin >> line;

        for (std::string::size_type j = 0; j < line.length(); j++) {
          int row = (i+j)/cols, col = (i+j)%cols;
          if (line[j] == '0')
            bit_maps[row][col] = false;
          else
            bit_maps[row][col] = true;
        }

        i += line.length();
      }

      std::cout << "D" << std::setw(4) << rows << std::setw(4) << cols;
      std::string result = transformB2D(bit_maps, 0, rows, 0, cols);
      for (std::string::size_type i = 0; i < result.length(); i++) {
        if (i%50 == 0)
          std::cout << '\n';
        std::cout << result[i];
      }
      std::cout << '\n';
    } else {
      std::vector<std::vector<char>> bit_maps (rows, std::vector<char> (cols));
      std::queue<char> queue;

      transformD2B(bit_maps, queue, 0, rows, 0, cols);

      std::cout << "B" << std::setw(4) << rows << std::setw(4) << cols;
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          if ((i*cols+j) % 50 == 0)
            std::cout << '\n';
          std::cout << bit_maps[i][j];
        }
      }
      std::cout << '\n';
    }
  }

  return 0;
}
