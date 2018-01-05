#include <cmath>
#include <iostream>
#include <vector>

bool isPrime(int number)
{
  for (int i = 2; i <= sqrt(number); i++)
    if (number % i == 0)
      return false;

  return true;
}

void print(std::vector<int> &ring)
{
  for (std::vector<int>::size_type i = 0; i < ring.size(); i++) {
    if (i != 0)
      std::cout << ' ';

    std::cout << ring[i];
  }
  std::cout << '\n';
}

void solve(std::vector<int> &ring,
           std::vector<bool> &numbers,
           const std::vector<bool> &prime_table,
           int n)
{
  if (n == 0) {
    if (prime_table[ring.front() + ring.back()])
      print(ring);

    return;
  }

  for (std::vector<bool>::size_type i = 1; i < numbers.size(); i++) {
    if (!numbers[i])
      continue;

    if (!ring.empty() && !prime_table[i+ring.back()])
      continue;

    numbers[i] = false;
    ring.push_back(i);
    solve(ring, numbers, prime_table, n - 1);
    ring.pop_back();
    numbers[i] = true;
  }
}

int main(void)
{
  int n, count = 1;

  while (std::cin >> n) {
    if (count != 1)
      std::cout << '\n';
    std::cout << "Case " << count << ":\n";

    // compute the table of prime
    std::vector<bool> prime_table(n+n+1, false);
    for (std::vector<bool>::size_type i = 1; i < prime_table.size(); i++)
      prime_table[i] = isPrime(i);

    std::vector<int> ring = {1};
    std::vector<bool> numbers(n+1, true);
    numbers[1] = false;

    solve(ring, numbers, prime_table, n-1);

    count++;
  }

  return 0;
}
