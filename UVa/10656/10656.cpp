#include <climits>

#include <iostream>
#include <stack>
#include <vector>

int main(void)
{
  int number_of_numbers;

  while (std::cin >> number_of_numbers)
  {
    if (number_of_numbers == 0)
      break;

    std::vector<unsigned> numbers;

    for (int i = 0; i < number_of_numbers; i++)
    {
      unsigned number;
      std::cin >> number;

      if (number > 0)
        numbers.push_back(number);
    }

    if (numbers.size() == 0)
      numbers.push_back(0);

    for (std::size_t i = 0; i < numbers.size()-1; i++)
      std::cout << numbers[i] << ' ';
    std::cout << numbers[numbers.size()-1] << '\n';
  }

  return 0;
}
