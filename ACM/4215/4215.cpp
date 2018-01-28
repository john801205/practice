#include <iostream>

int main(void)
{
  int N;

  while (std::cin >> N and N != 0)
  {
    // int squares = 0;

    // for (int i = 1; i <= N; i++)
    //   squares += (N-i+1) * (N-i+1);

    std::cout << N*(N+1)*(2*N+1)/6 << '\n';
  }

  return 0;
}
