#include <iostream>

// ceiling_divide returns ceil(a/b)
unsigned long long ceiling_divide(
    unsigned long long a,
    unsigned long long b
)
{
  return (a % b == 0? a/b: a/b + 1);
}

int main()
{
  // n: the number of vertices in a plot of a piecewise function
  // k: the area we need to obtain
  unsigned long long n, k;
  std::cin >> n >> k;

  // Each move increases the total area one. Hence, to reduce the minimum
  // height, we should move every possible vertices to same height before
  // reaching the target area. So, the minimum height is ceil(a/b).
  std::cout << ceiling_divide(k, n) << '\n';

  return 0;
}
