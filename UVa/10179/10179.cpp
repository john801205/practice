#include <cmath>

#include <iostream>
#include <vector>

#define MAX_NUMBER 1000000000

std::vector<unsigned> sieve(unsigned n)
{
  if (n == 1 or n == 2)
    return std::vector<unsigned> ();

  std::vector<unsigned> primes;
  std::vector<bool> tables (n, true);

  tables[0] = false;
  tables[1] = false;

  for (std::vector<bool>::size_type i = 2; i < tables.size(); i++)
  {
    if (!tables[i])
      continue;

    primes.push_back(i);
    for (std::vector<bool>::size_type j = i + i; j < tables.size(); j+=i)
    {
      tables[j] = false;
    }
  }

  return primes;
}

unsigned number_of_coprime(unsigned n)
{
  if (n == 1 || n == 2)
    return 1;

  const static std::vector<unsigned> primes = sieve(sqrt(MAX_NUMBER+1));
  unsigned count = n;
  unsigned temp  = n;

  for (std::vector<unsigned>::size_type i = 0; i < primes.size() && temp != 1; i++)
  {
    if (primes[i] > sqrt(temp))
      break;

    if (temp % primes[i] != 0)
      continue;

    do {
      temp /= primes[i];
    } while (temp % primes[i] == 0);

    count = count / primes[i] * (primes[i] - 1);
  }

  if (temp != 1)
  {
    count = count / temp * (temp - 1);
  }

  return count;
}

int main(void)
{
  unsigned n;

  while (std::cin >> n && n != 0)
  {
    std::cout << number_of_coprime(n) << '\n';
  }

  return 0;
}
