#include <climits>
#include <cmath>

#include <array>
#include <iostream>
#include <vector>

#define NUM_MAX 18409202

int main(void)
{
  std::vector<bool> primes(NUM_MAX, true);

  primes[0] = false;
  primes[1] = false;
  for (unsigned i = 2; i < floor(sqrt(NUM_MAX)); i++)
  {
    if (!primes[i])
      continue;

    for (unsigned j = i + i; j < NUM_MAX; j += i)
      primes[j] = false;
  }

  std::vector<std::array<unsigned, 2>> tables;
  for (unsigned i = 2; i+2 < NUM_MAX; i++)
  {
    if (primes[i] and primes[i+2])
    {
      tables.push_back(std::array<unsigned, 2> {i, i+2});
    }
  }

  unsigned N;

  while (std::cin >> N)
    std::cout << '(' << tables[N-1][0] << ", " << tables[N-1][1] << ")\n";

  return 0;
}
