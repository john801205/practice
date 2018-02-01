#include <iostream>

#define MAX 1000000

int reverse(int N)
{
  int r = 0;
  while (N != 0)
  {
    r = 10 * r + (N % 10);
    N = N / 10;
  }

  return r;
}

int main(void)
{
  bool primes[MAX];

  primes[0] = false;
  primes[1] = false;
  for (int num = 2; num < MAX; num++)
    primes[num] = true;

  for (int num = 2; num < MAX; num++)
  {
    if (primes[num])
    {
      for (int i = num+num; i < MAX; i += num)
        primes[i] = false;
    }
  }

  int N;
  while (std::cin >> N)
  {
    if (!primes[N])
      std::cout << N << " is not prime.\n";
    else if (N == reverse(N) or !primes[reverse(N)])
      std::cout << N << " is prime.\n";
    else
      std::cout << N << " is emirp.\n";
  }

  return 0;
}
