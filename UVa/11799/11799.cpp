#include <iostream>
#include <climits>

int main(void)
{
  int T;

  while(std::cin >> T) {
    for(int t = 1; t <= T; t++) {
      int N, value, max;

      std::cin >> N;

      max = INT_MIN;
      for(int i = 0; i < N; i++) {
        std::cin >> value;
        if (value > max)
          max = value;
      }

      std::cout << "Case " << t << ": " << max << std::endl;
    }
  }

  return 0;
}
