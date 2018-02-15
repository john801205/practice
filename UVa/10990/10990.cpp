#include <cmath>

#include <iostream>
#include <vector>

const unsigned MAX_NUMBER = 2000000;

std::vector<unsigned> sieve(unsigned n)
{
  if (n == 0 || n == 1)
    return {};

  std::vector<unsigned> primes;
  std::vector<bool>     numbers (n, true);

  for (std::vector<bool>::size_type i = 2; i < numbers.size(); i++)
  {
    if (!numbers[i])
      continue;

    primes.push_back(i);
    for (std::vector<bool>::size_type j = i+i; j < numbers.size(); j += i)
      numbers[j] = false;
  }

  return primes;
}

unsigned totient(unsigned n)
{
  if (n < 2)
    return 0;

  static const std::vector<unsigned> primes = sieve(sqrt(MAX_NUMBER));

  unsigned value = n;
  for (std::vector<unsigned>::size_type i = 0; i < primes.size(); i++)
  {
    if (n == 1 || primes[i] > sqrt(n))
      break;

    if (n % primes[i] != 0)
      continue;

    do
    {
      n /= primes[i];
    }
    while (n % primes[i] == 0);

    value = value / primes[i] * (primes[i] - 1);
  }

  if (n != 1)
    value = value / n * (n - 1);

  return value;
}

int main(void)
{
  std::vector<unsigned> depthphi (MAX_NUMBER+1, 0);

  for (std::vector<unsigned>::size_type i = 2; i < depthphi.size(); i++)
    depthphi[i] = depthphi[totient(i)] + 1;

  // cumulated sum
  for (std::vector<unsigned>::size_type i = 1; i < depthphi.size(); i++)
    depthphi[i] = depthphi[i-1] + depthphi[i];

  unsigned number_of_tests;

  while (std::cin >> number_of_tests)
  {
    for (unsigned test = 0; test < number_of_tests; test++)
    {
      unsigned m, n;
      std::cin >> m >> n;

      std::cout << depthphi[n] - depthphi[m-1] << '\n';
    }
  }

  return 0;
}
