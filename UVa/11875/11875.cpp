#include <iostream>

int main(void)
{
  std::ios::sync_with_stdio(false);

  int number_of_tests;

  while (std::cin >> number_of_tests)
  {
    for (int test = 1; test <= number_of_tests; test++)
    {
      int number_of_players, age;
      std::cin >> number_of_players;

      for (int i = 0; i < number_of_players/2; i++)
        std::cin >> age;

      std::cin >> age;
      std::cout << "Case " << test << ": " << age << '\n';

      for (int i = 0; i < number_of_players/2; i++)
        std::cin >> age;
    }
  }

  return 0;
}
