#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main(void)
{
  int number_of_tests;
  std::cin >> number_of_tests;

  for (int test = 1; test <= number_of_tests; test++)
  {
    int number_of_ingredients, number_of_packages;
    std::cin >> number_of_ingredients >> number_of_packages;

    std::vector<int> requirements (number_of_ingredients);
    for (int i = 0; i < number_of_ingredients; i++)
      std::cin >> requirements[i];

    std::vector<std::vector<int>> packages (number_of_ingredients);
    for (int i = 0; i < number_of_ingredients; i++)
    {
      for (int j = 0; j < number_of_packages; j++)
      {
        int package;
        std::cin >> package;

        int min1 = std::ceil(package / 1.1 / requirements[i]);
        int max1 = std::floor(package / 0.9 / requirements[i]);

        if (min1 <= max1)
        {
          packages[i].emplace_back(package);
        }
      }
    }

    for (int i = 0; i < number_of_ingredients; i++)
      std::sort(std::begin(packages[i]), std::end(packages[i]));

    std::vector<int> indexes (number_of_ingredients, 0);
    int count = 0;

    while (true)
    {
      bool failed = false, restart = false;
      for (int i = 0; i < number_of_ingredients && !failed; i++)
        if (indexes[i] >= packages[i].size())
          failed = true;

      if (failed)
        break;

      for (int i = 0; i < number_of_ingredients; i++)
      {
        int min1 = std::ceil(packages[i][indexes[i]] / 1.1 / requirements[i]);
        int max1 = std::floor(packages[i][indexes[i]] / 0.9 / requirements[i]);

        for (int j = i+1; j < number_of_ingredients; j++)
        {
          int min2 = std::ceil(packages[j][indexes[j]] / 1.1 / requirements[j]);
          int max2 = std::floor(packages[j][indexes[j]] / 0.9 / requirements[j]);

          // std::cerr << indexes[i] << '(' << min1 << ',' << max1 << ')' << ' '
          //           << indexes[j] << '(' << min2 << ',' << max2 << ')' << '\n';
          while (max2 < min1)
          {
            restart = true;
            indexes[j]++;
            if (indexes[j] >= packages[j].size())
              break;

            max2 = std::floor(packages[j][indexes[j]] / 0.9 / requirements[j]);
          }

          while (min2 > max1)
          {
            restart = true;
            indexes[i]++;
            if (indexes[i] >= packages[i].size())
              break;

            max1 = std::floor(packages[i][indexes[i]] / 0.9 / requirements[i]);
          }
        }
      }

      // std::cerr << "restart: " << restart << '\n';
      if (restart)
        continue;

      count++;
      for (int i = 0; i < number_of_ingredients; i++)
        indexes[i]++;
    }

    std::cout << "Case #" << test << ": " << count << "\n";
  }

  return 0;
}
