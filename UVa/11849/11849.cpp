#include <iostream>
#include <unordered_set>

int main(void)
{
  unsigned N, M;

  while (std::cin >> N >> M) {
    if (N == 0 && M == 0)
      break;

    std::unordered_set<unsigned> Jack;
    for (unsigned i = 0, cd; i < N; i++) {
      std::cin >> cd;
      Jack.insert(cd);
    }

    unsigned duplicates = 0;
    for (unsigned i = 0, cd; i < M; i++) {
      std::cin >> cd;
      if (Jack.count(cd) > 0)
        duplicates++;
    }

    std::cout << duplicates << std::endl;
  }

  return 0;
}
