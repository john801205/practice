#include <cmath>

#include <iomanip>
#include <iostream>

int main(void)
{
  int number_of_test_cases;

  std::cout << std::fixed;
  std::cout << std::setprecision(3);

  std::cin >> number_of_test_cases;
  for (int case_ = 1; case_ <= number_of_test_cases; case_++)
  {
    double d, v, u;

    std::cin >> d >> v >> u;

    if (u > v and v != 0)
    {
      double fastest = d / u,
             shortest = sqrt(d*d / (u*u - v*v));

      std::cout << "Case " << case_ << ": " << shortest - fastest << '\n';
    }
    else
    {
      std::cout << "Case " << case_ << ": can't determine\n";
    }
  }

  return 0;
}
