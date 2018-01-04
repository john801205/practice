#include <climits>

#include <algorithm>
#include <iostream>
#include <vector>

int main(void)
{
  int number_of_problems;

  while (std::cin >> number_of_problems) {
    for (int problem = 0; problem < number_of_problems; problem++) {
      int number_of_coin_types, target_emodulus;
      std::cin >> number_of_coin_types >> target_emodulus;

      std::vector<std::vector<int>> tables (target_emodulus+1, std::vector<int> (target_emodulus+1, INT_MAX));
      tables[0][0] = 0;

      for (int i = 0, convention, infotech; i < number_of_coin_types; i++) {
        std::cin >> convention >> infotech;

        for (int x = 0; x <= target_emodulus - convention; x++) {
          for (int y = 0; y <= target_emodulus - infotech; y++) {
            if (tables[x][y] == INT_MAX)
              continue;

            tables[x+convention][y+infotech] = std::min(tables[x+convention][y+infotech], tables[x][y]+1);
          }
        }
      }

      int min_coins = INT_MAX;
      for (int x = 0; x <= target_emodulus; x++) {
        for (int y = 0; y <= target_emodulus; y++) {
          if (tables[x][y] == INT_MAX)
            continue;

          if (x*x + y*y != target_emodulus*target_emodulus)
            continue;

          min_coins = std::min(min_coins, tables[x][y]);
        }
      }

      if (min_coins == INT_MAX)
        std::cout << "not possible\n";
      else
        std::cout << min_coins << '\n';
    }
  }

  return 0;
}
