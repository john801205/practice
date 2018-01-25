#include <cmath>
#include <iomanip>
#include <iostream>

int main(void)
{
  std::cout << std::fixed;
  std::cout << std::setprecision(3);

  int number_of_tests;

  while (std::cin >> number_of_tests)
  {
    for (int i = 0; i < number_of_tests; i++)
    {
      if (i != 0)
        std::cout << '\n';

      int size_of_dashboard;

      std::cin >> size_of_dashboard;

      double length = 0;

      if (size_of_dashboard > 2)
        length += sqrt(2) * pow(size_of_dashboard-2, 2)
                  + (size_of_dashboard-2) * 2;

      if (size_of_dashboard > 1)
        length += size_of_dashboard * 2;

      std::cout << length << '\n';
    }
  }

  return 0;
}
