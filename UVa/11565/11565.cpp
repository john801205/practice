#include <cmath>
#include <iostream>

int main(void)
{
  int N;

  while (std::cin >> N) {
    for (int i = 0; i < N; i++) {
      int A, B, C;
      bool sol = false;

      std::cin >> A >> B >> C;

      int limit = ceil(sqrt(C));
      for (int x = -limit; x <= limit && !sol; x++) {
        for (int y = x+1; y <= limit && !sol; y++) {
          int z = A - x - y;

          if (x == y || y == z || x == z)
            continue;

          if (x*y*z != B)
            continue;

          if (x*x + y*y + z*z != C)
            continue;

          sol = true;
          std::cout << x << ' ' << y << ' ' << z << '\n';
        }
      }

      if (!sol)
        std::cout << "No solution.\n";
    }
  }

  return 0;
}
