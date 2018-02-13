#include <cmath>

#include <iostream>
#include <vector>

#define MAX_NUMBER 1000000000

std::vector<unsigned> sieve(const unsigned n)
{
  std::vector<unsigned> result;
  std::vector<bool> tables (n, true);

  tables[0] = false;
  tables[1] = false;

  for (std::vector<bool>::size_type i = 2; i < n; i++)
  {
    if (!tables[i])
      continue;

    result.push_back(i);

    for (std::vector<bool>::size_type j = i + i; j < n; j+=i)
      tables[j] = false;
  }

  return result;
}

unsigned number_of_divisors(const unsigned n)
{
  const static std::vector<unsigned> primes = sieve(sqrt(MAX_NUMBER+1));

  unsigned divisors = 1;
  unsigned temp     = n;

  for (std::vector<unsigned>::size_type i = 0; i < primes.size() && temp != 1; i++)
  {
    if (primes[i] > sqrt(temp))
      break;

    if (temp % primes[i] != 0)
      continue;

    unsigned count = 0;
    for (count = 0; temp % primes[i] == 0; temp /= primes[i])
      count++;

    divisors *= (count + 1);
  }

  if (temp != 1)
    divisors *= 2;

  return divisors;
}


int main(void)
{
  unsigned N;

  while (std::cin >> N)
  {
    while (N-- > 0)
    {
      unsigned L, U;
      std::cin >> L >> U;

      unsigned max_divisors = 0, max_number = 0;

      for (unsigned number = L; number <= U; number++)
      {
        unsigned divisors = number_of_divisors(number);
        if (divisors > max_divisors)
        {
          max_divisors = divisors;
          max_number = number;
        }
      }

      std::cout << "Between " << L << " and " << U << ", "
                << max_number << " has a maximum of "
                << max_divisors << " divisors.\n";
    }
  }

  return 0;
}
