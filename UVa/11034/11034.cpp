#include <iostream>
#include <queue>
#include <string>

int main(void)
{
  int number_of_test_cases;

  while (std::cin >> number_of_test_cases) {
    for (int case_ = 0; case_ < number_of_test_cases; case_++) {
      int l, m;
      std::queue<int> banks[2];

      std::cin >> l >> m;

      // convert from meters to centimeters
      l = l * 100;

      for (int i = 0; i < m; i++) {
        int length;
        std::string pos;

        std::cin >> length >> pos;
        if (pos.compare("left") == 0)
          banks[0].push(length);
        else
          banks[1].push(length);
      }

      // 0 -> left, 1 -> right
      int ferry_pos = 0, cross = 0;

      while (!banks[0].empty() || !banks[1].empty()) {
        int total_lengths = 0;

        // load as many cars as possible
        while (!banks[ferry_pos].empty()
               && total_lengths+banks[ferry_pos].front() <= l) {
          total_lengths += banks[ferry_pos].front();
          banks[ferry_pos].pop();
        }

        // cross the river
        ferry_pos = 1 - ferry_pos;
        cross += 1;
      }

      std::cout << cross << std::endl;
    }
  }

  return 0;
}
