#include <iostream>
#include <stack>
#include <string>

int main(void)
{
  int N;

  while (std::cin >> N) {
    if (N == 0)
      break;


    while (true) {
      std::stack<int> station;
      int coach, max_coach;

      max_coach = 0;
      for (int i = 0; i < N; i++) {
        std::cin >> coach;

        if (coach == 0)
          break;

        if (coach > max_coach) {
          for (int j = max_coach+1; j <= coach; j++)
            station.push(j);
          max_coach = coach;
        }

        if (station.top() == coach) {
          station.pop();
        } else {
          std::string line;
          std::getline(std::cin, line); // discard remaining input
          break;
        }
      }

      if (coach == 0) {
        std::cout << std::endl;
        break;
      } else if (station.size() != 0) {
        std::cout << "No" << std::endl;
      } else {
        std::cout << "Yes" << std::endl;
      }
    }
  }

  return 0;
}
