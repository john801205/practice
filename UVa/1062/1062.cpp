#include <climits>

#include <iostream>
#include <string>
#include <list>

int main(void)
{
  std::string line;
  int number_of_cases = 1;

  while (std::getline(std::cin, line)) {
    if (line.compare("end") == 0)
      break;

    std::list<char> containers {line.begin(), line.end()};
    unsigned number_of_stacks = 0;

    while (!containers.empty()) {
      char current = CHAR_MAX;
      auto it = containers.begin();

      while (it != containers.end()) {
        if (*it <= current) {
          current = *it;
          it = containers.erase(it);
        } else {
          ++it;
        }
      }

      number_of_stacks++;
    }

    std::cout << "Case " << number_of_cases << ": " << number_of_stacks << std::endl;
    number_of_cases++;
  }


  return 0;
}
