#include <iostream>
#include <vector>

int my_module(int a, int b)
{
  int r = a % b;
  if (r < 0)
    r += b;
  return r;
}

unsigned long long solve(const std::vector<int> &numbers, const int D, const int M)
{
  // not so much numbers can be selected
  if (numbers.size() < unsigned(M))
    return 0;

  // result[i][j] represents the number of last number index is i and modulus of sum is j
  std::vector<std::vector<unsigned long long>> result (numbers.size(),
                                                       std::vector<unsigned long long> (D, 0));

  // set the initial condition when only select 1 number
  for (std::vector<int>::size_type i = 0; i < numbers.size(); i++)
    result[i][my_module(numbers[i], D)] = 1;

  // m represents how many number are already selected
  for (int m = 1; m < M; m++)
  {
    // number_of_modulus[i] stores the number of modulus i
    // when m numbers are selected
    std::vector<unsigned long long> number_of_modulus (D, 0);
    for (const auto &number: result)
    {
      for (int modulus = 0; modulus < D; modulus++)
      {
        number_of_modulus[modulus] += number[modulus];
      }
    }

    // numbers[i] is current selected number
    for (int i = numbers.size()-1; i >= m; i--)
    {
      // update number_of_modulus[i] to stores the number of modulus
      // when numbers of index less than i are selected
      for (int modulus = 0; modulus < D; modulus++)
      {
        number_of_modulus[modulus] -= result[i][modulus];
      }

      for (int modulus = 0; modulus < D; modulus++)
      {

        // (target + numbers[i]) % D == modulus
        int target = my_module(modulus - my_module(numbers[i], D), D);
        result[i][modulus] = number_of_modulus[target];
      }
    }

    for (int i = m-1; i >= 0; i--)
    {
      for (int modulus = 0; modulus < D; modulus++)
      {
        result[i][modulus] = 0;
      }
    }
  }

  unsigned long long count = 0;
  for (std::vector<int>::size_type i = 0; i < numbers.size(); i++)
    count += result[i][0];

  return count;
}

int main(void)
{
  int N, Q, count = 1;

  while (std::cin >> N >> Q)
  {
    if (N == 0 && Q == 0)
      break;

    std::cout << "SET " << count << ":\n";

    std::vector<int> numbers(N);
    for (std::vector<int>::size_type i = 0; i < numbers.size(); i++)
      std::cin >> numbers[i];

    for (int query = 1; query <= Q; query++)
    {
      int D, M;
      std::cin >> D >> M;
      std::cout << "QUERY " << query << ": " << solve(numbers, D, M) << '\n';
    }

    count++;
  }

  return 0;
}
