#include <iomanip>
#include <iostream>

int main(void)
{
  std::cout << std::fixed << std::setprecision(6);

  int number_of_tests;
  std::cin >> number_of_tests;

  for (int test = 1; test <= number_of_tests; test++)
  {
    double required_time = 0;

    int destination, number_of_horses;
    std::cin >> destination >> number_of_horses;

    for (int horse = 0; horse < number_of_horses; horse++)
    {
      int position, speed;
      std::cin >> position >> speed;

      double time = static_cast<double>(destination - position) / speed;
      required_time = std::max(required_time, time);
    }

    std::cout << "Case #" << test << ": " << destination / required_time << '\n';
  }

  return 0;
}
