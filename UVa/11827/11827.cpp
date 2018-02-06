#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int gcd(int a, int b)
{
  while (b != 0)
  {
    int r = a % b;
    a = b;
    b = r;
  }

  return a;
}

int main(void)
{
  int N;

  while (std::cin >> N)
  {
    // ignore new line
    std::cin.ignore();

    for (int i = 0; i < N; i++)
    {
      std::string line;
      std::getline(std::cin, line);
      std::istringstream stream(line);

      std::vector<int> numbers;
      int max_gcd = 1, number;

      while (stream >> number)
        numbers.emplace_back(number);

      for (std::vector<int>::size_type i = 0; i < numbers.size(); i++)
      {
        for (std::vector<int>::size_type j = i+1; j < numbers.size(); j++)
        {
          max_gcd = std::max(gcd(numbers[i], numbers[j]), max_gcd);
        }
      }

      std::cout << max_gcd << '\n';
    }
  }

  return 0;
}
