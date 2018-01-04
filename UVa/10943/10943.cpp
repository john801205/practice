#include <iostream>
#include <vector>

int main(void)
{
  int N, K;

  while (std::cin >> N >> K) {
    if (N == 0 && K == 0)
      break;

    // tables[i] stores the answer for number i
    // for K == 1, every one is 1
    std::vector<int> tables (N+1, 1);


    // for each k
    for (int k = 1; k < K; k++) {
      // for each number i
      for (int i = 1; i <= N; i++) {
        // tables'[i] = sum_(tables[j]) for j=0..i
        // tables'[1] = tables[0] + tables[1]
        // tables'[2] = tables[0] + tables[1] + tables[2]
        //            = tables'[1] + tables[2]
        //
        // tables[i] = tables[i-1] + tables[i];
        tables[i] = (tables[i-1]+tables[i]) % 1000000;
      }
    }

    std::cout << tables[N] << '\n';
  }

  return 0;
}
