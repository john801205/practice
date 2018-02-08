#include <climits>
#include <cmath>

#include <iostream>
#include <vector>

#define MAX_NUMBER 2147483647

std::vector<unsigned> prime_table (unsigned n)
{
  if (n < 2)
    return std::vector<unsigned> ();

  // build a vector of prime numbers up to n
  std::vector<unsigned> prime_numbers = {2};

  for (unsigned number = 3; number <= n; number++)
  {
    bool prime = true;

    for (const auto &prime_number: prime_numbers)
    {
      if (prime_number > sqrt(number))
        break;

      if (number % prime_number == 0)
      {
        prime = false;
        break;
      }
    }

    if (prime)
      prime_numbers.emplace_back(number);
  }

  return prime_numbers;
}

bool is_prime(unsigned n)
{
  static const std::vector<unsigned> prime_numbers = prime_table(sqrt(MAX_NUMBER));

  if (n < 2)
    return false;

  for (const auto &prime_number: prime_numbers)
  {
    if (prime_number > sqrt(n))
      break;

    if (n % prime_number == 0)
      return false;
  }

  return true;
}

int main(void)
{
  unsigned L, U;

  while (std::cin >> L >> U)
  {
    unsigned min_distance = UINT_MAX;
    unsigned min_prime_1  = 0;
    unsigned min_prime_2  = 0;

    unsigned max_distance = 0;
    unsigned max_prime_1  = 0;
    unsigned max_prime_2  = 0;

    unsigned previous_prime = L-1;

    for (unsigned number = L; number <= U; number++)
    {
      if (!is_prime(number))
        continue;

      // std::cerr << number << '\n';

      if (previous_prime != L-1 and number-previous_prime < min_distance)
      {
        min_distance = number - previous_prime;
        min_prime_1  = previous_prime;
        min_prime_2  = number;
      }

      if (previous_prime != L-1 and number-previous_prime > max_distance)
      {
        max_distance = number - previous_prime;
        max_prime_1  = previous_prime;
        max_prime_2  = number;
      }

      previous_prime = number;
    }

    if (min_distance == UINT_MAX)
      std::cout << "There are no adjacent primes.\n";
    else
      std::cout << min_prime_1 << ',' << min_prime_2 << " are closest, "
                << max_prime_1 << ',' << max_prime_2 << " are most distant.\n";
  }

  return 0;
}
