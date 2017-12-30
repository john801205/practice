#include <climits>
#include <cmath>

#include <iostream>
#include <vector>
#include <utility>

struct Cell {
  int x, y;

  Cell(int x_, int y_): x(x_), y(y_) {}
};

int main(void)
{
  int M;

  while (std::cin >> M) {
    std::vector<Cell> ones, threes;
    char cell;

    for (int i = 0; i < M; i++) {
      for (int j = 0; j < M; j++) {
        std::cin >> cell;

        if (cell == '1')
          ones.push_back(Cell(i, j));
        else if (cell == '3')
          threes.push_back(Cell(i, j));
      }
    }

    int max_distance = INT_MIN;
    for (const auto& one: ones) {
      int min_distance = INT_MAX;

      for (const auto& three: threes) {
        int distance = abs(three.x - one.x) + abs(three.y - one.y);
        if (distance < min_distance)
          min_distance = distance;
      }

      if (min_distance > max_distance)
        max_distance = min_distance;
    }

    std::cout << max_distance << '\n';
  }

  return 0;
}
