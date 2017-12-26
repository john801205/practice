#include <climits>
#include <cstdlib>

#include <array>
#include <iostream>

int main(void)
{
  for (int case_ = 1; ; case_++) {
    int number_of_integers, number_of_queries;

    std::cin >> number_of_integers;
    if (number_of_integers == 0)
      break;

    int *integers = new int[number_of_integers];
    for (int i = 0; i < number_of_integers; i++)
      std::cin >> integers[i];

    std::cin >> number_of_queries;

    std::cout << "Case " << case_ << ":\n";
    for (int i = 0, query; i < number_of_queries; i++) {
      std::cin >> query;

      int sum = INT_MAX, distance = INT_MAX;
      for (int j = 0; j < number_of_integers; j++) {
        for (int k = j + 1; k < number_of_integers; k++) {
          if (std::abs(integers[j] + integers[k] - query) < distance) {
            distance = std::abs(integers[j] + integers[k] - query);
            sum = integers[j] + integers[k];
          }
        }
      }

      std::cout << "Closest sum to " << query << " is " << sum << ".\n";
    }

    delete[] integers;
  }

  return 0;
}
