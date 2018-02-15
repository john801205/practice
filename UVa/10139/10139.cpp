#include <cmath>

#include <iostream>
#include <vector>

const unsigned MAX_NUMBER = 2147483648;

struct PrimeFactor
{
  const unsigned prime, exp;

  PrimeFactor(const unsigned prime, const unsigned exp): prime(prime), exp(exp) {}
};

std::vector<unsigned> sieve(const unsigned n)
{
  std::vector<unsigned> primes;
  std::vector<bool>     numbers (n, true);

  for (std::vector<bool>::size_type i = 2; i < numbers.size(); i++)
  {
    if (!numbers[i])
      continue;

    primes.push_back(i);

    for (std::vector<bool>::size_type j = i + i; j < numbers.size(); j+=i)
      numbers[j] = false;
  }

  return primes;
}

std::vector<PrimeFactor> prime_factorization(const unsigned n)
{
  if (n == 0 || n == 1)
    return std::vector<PrimeFactor> ();

  static const std::vector<unsigned> primes = sieve(sqrt(MAX_NUMBER));

  std::vector<PrimeFactor> result;
  unsigned temp_n = n;
  for (std::vector<unsigned>::size_type i = 0; i < primes.size(); i++)
  {
    if (temp_n == 1 || primes[i] > sqrt(temp_n))
      break;

    if (temp_n % primes[i] != 0)
      continue;

    unsigned exp = 0;
    do
    {
      exp++;
      temp_n /= primes[i];
    }
    while (temp_n % primes[i] == 0);

    result.emplace_back(primes[i], exp);
  }

  if (temp_n != 1)
  {
    result.emplace_back(temp_n, 1);
  }

  return result;
}

unsigned count(unsigned factorial, unsigned prime)
{
  unsigned exp = 0;

  while (factorial >= prime)
  {
    exp += factorial / prime;
    factorial /= prime;
  }

  return exp;
}

int main(void)
{
  unsigned factorial, divisor;

  while (std::cin >> factorial >> divisor)
  {
    const std::vector<PrimeFactor> factors = prime_factorization(divisor);

    bool divides = true;
    for (std::vector<PrimeFactor>::size_type i = 0; i < factors.size(); i++)
    {
      if (count(factorial, factors[i].prime) < factors[i].exp)
      {
        divides = false;
        break;
      }
    }

    std::cout << divisor
              << (divides ? " divides ": " does not divide ")
              << factorial << "!\n";
  }

  return 0;
}
