#include <iostream>
#include <queue>
#include <vector>
#include <functional>

int main(void)
{
  int N;

  while (std::cin >> N) {
    if (N == 0)
      break;

    std::priority_queue<int, std::vector<int>, std::greater<int>> numbers;

    for (int i = 0, number; i < N; i++) {
      std::cin >> number;
      numbers.push(number);
    }

    int cost = 0;

    while (numbers.size() > 1) {
      const auto a = numbers.top();
      numbers.pop();
      const auto b = numbers.top();
      numbers.pop();

      const auto sum = a + b;
      cost += sum;
      numbers.push(sum);
    }

    std::cout << cost << '\n';
  }

  return 0;
}
