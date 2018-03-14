#include <iostream>

int main(void)
{
  unsigned case_ = 0;
  unsigned number_of_roads, number_of_integers;

  std::ios_base::sync_with_stdio(false);
  while (std::cin >> number_of_roads >> number_of_integers)
  {
    if (number_of_roads == 0 && number_of_integers == 0)
    {
      break;
    }

    std::cout << "Case " << ++case_ << ": ";
    if (number_of_roads > number_of_integers * 27)
      std::cout << "impossible";
    else if (number_of_roads % number_of_integers == 0)
      std::cout << number_of_roads / number_of_integers - 1;
    else
      std::cout << number_of_roads / number_of_integers;
    std::cout << '\n';
  }

  return 0;
}
