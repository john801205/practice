#include <cmath>

#include <iostream>
#include <vector>

const unsigned MAX_NUMBER = 2147483648;

std::vector<unsigned> sieve(unsigned n)
{
  std::vector<unsigned> primes;
  std::vector<bool>     numbers (n, true);

  numbers[0] = false;
  numbers[1] = false;

  for (std::vector<bool>::size_type i = 2; i < numbers.size(); i++)
  {
    if (!numbers[i])
      continue;

    primes.push_back(i);

    for (std::vector<bool>::size_type j = i + i; j < numbers.size(); j += i)
      numbers[j] = false;
  }

  return primes;
}

int main(void)
{
  static const std::vector<unsigned> primes = sieve(sqrt(MAX_NUMBER));
  int number;

  while (std::cin >> number && number != 0)
  {
    bool first = true;

    std::cout << number << " = ";

    if (number < 0)
    {
      std::cout << -1;
      number *= -1;
      first = false;
    }

    for (std::vector<unsigned>::size_type i = 0; i < primes.size(); i++)
    {
      if (number == 1 || primes[i] > sqrt(number))
        break;

      if (number % primes[i] != 0)
        continue;

      do 
      {
        if (!first)
          std::cout << " x ";

        std::cout << primes[i];
        number /= primes[i];
        first = false;
      }
      while (number % primes[i] == 0);
    }

    if (number != 1)
    {
      if (!first)
        std::cout << " x ";

      std::cout << number;
      first = false;
    }

    std::cout << '\n';
  }

  return 0;
}
