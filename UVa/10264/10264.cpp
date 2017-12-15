#include <iostream>
#include <climits>

int main(void)
{
  int N;

  while (std::cin >> N) {
    int number_of_corners, *potencies;

    number_of_corners = 1 << N;
    potencies = new int[number_of_corners];

    for (int i = 0; i < number_of_corners; i++)
      potencies[i] = 0;

    for (int i = 0; i < number_of_corners; i++) {
      int weight;
      std::cin >> weight;

      for (int bit = 0; bit < N; bit++) {
        int neighbor = i ^ (1 << bit);
        potencies[neighbor] += weight;
      }
    }

    int max_sum = INT_MIN;
    for (int i = 0; i < number_of_corners; i++) {
      for (int bit = 0; bit < N; bit++) {
        int neighbor = i ^ (1 << bit);
        if (potencies[i] + potencies[neighbor] > max_sum)
          max_sum = potencies[i] + potencies[neighbor];
      }
    }

    std::cout << max_sum << std::endl;

    delete[] potencies;
  }

  return 0;
}
