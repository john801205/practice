#include <iostream>
#include <string>

#define WIDTH 3
#define HEIGHT 3

void getGrid(int grid[][WIDTH])
{
  std::string line;

  for (int row = 0; row < HEIGHT; row++) {
    std::getline(std::cin, line);

    for (int col = 0; col < WIDTH; col++) {
      if (line[col] == '0')
        grid[row][col] = 0;
      else
        grid[row][col] = 1;
    }
  }
}

bool f(int g[][WIDTH], int h[][WIDTH])
{
  bool changed = false;
  for (int row = 0; row < HEIGHT; row++) {
    for (int col = 0; col < WIDTH; col++) {
      int sum = 0;

      if (row > 0)
        sum += g[row-1][col];

      if (row < HEIGHT-1)
        sum += g[row+1][col];

      if (col > 0)
        sum += g[row][col-1];

      if (col < WIDTH-1)
        sum += g[row][col+1];

      h[row][col] = sum % 2;

      if (!changed && g[row][col] != h[row][col])
        changed = true;
    }
  }

  return changed;
}

int main(void)
{
  int N;

  while (std::cin >> N) {
    std::string line;

    std::getline(std::cin, line); // remove newline after number

    for (int i = 0; i < N; i++) {
      int g[HEIGHT][WIDTH] = {0}, h[HEIGHT][WIDTH] = {0};

      std::getline(std::cin, line); // remove empty line
      getGrid(g);

      int count = -1;

      while (true) {
        if (f(g, h))
          count++;
        else
          break;

        if (f(h, g))
          count++;
        else
          break;
      }

      std::cout << count << std::endl;
    }
  }

  return 0;
}
