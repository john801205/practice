#include <iostream>
#include <vector>

int solve(
    const std::vector<unsigned> &A,
    const std::vector<unsigned> &B
)
{
  std::vector<unsigned>::size_type i = 0, j = 0;
  long long difference = 0;
  int length = -1;

  while(i < A.size() && j < B.size())
  {
    if (difference == 0)
    {
      length++;

      difference = static_cast<long long>(A[i]) - B[j];
      i++;
      j++;
    }
    else if (difference < 0)
    {
      difference += A[i];
      i++;
    }
    else
    {
      difference -= B[j];
      j++;
    }
  }

  while (i < A.size())
  {
    difference += A[i];
    i++;
  }

  while (j < B.size())
  {
    difference -= B[j];
    j++;
  }

  if (difference != 0)
  {
    return -1;
  }
  else
  {
    // add one because the last two numbers are equal
    return length+1;
  }
}

int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // n: the length of the first array
  // m: the length of the second array
  unsigned n, m;
  // A: the first array
  // B: the second array
  std::vector<unsigned> A, B;

  std::cin >> n;
  A.resize(n);
  for (unsigned i = 0; i < n; ++i)
  {
    std::cin >> A[i];
  }

  std::cin >> m;
  B.resize(m);
  for (unsigned i = 0; i < m; ++i)
  {
    std::cin >> B[i];
  }

  std::cout << solve(A, B) << '\n';

  return 0;
}
