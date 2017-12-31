#include <climits>

#include <iostream>
#include <vector>

bool is_valid_capaciy(const std::vector<int>& vessels,
                            int number_of_containers,
                      const int capacity)
{
  int current_capacity = 0;

  for (std::vector<int>::size_type i = 0; i < vessels.size(); i++) {
    if (vessels[i] > capacity)
      return false;

    if (current_capacity < vessels[i]) {
      if (number_of_containers <= 0)
        return false;

      number_of_containers--;
      current_capacity = capacity;
    }

    current_capacity -= vessels[i];
  }

  return true;
}

int main(void)
{
  int number_of_vessels, number_of_containers;

  while (std::cin >> number_of_vessels >> number_of_containers) {
    std::vector<int> vessels (number_of_vessels);
    int min_capacity = INT_MIN, max_capacity = 0;

    for (int i = 0; i < number_of_vessels; i++) {
      std::cin >> vessels[i];

      if (vessels[i] > min_capacity)
        min_capacity = vessels[i];
      max_capacity += vessels[i];
    }

    // std::cerr << "===========\n";

    while (min_capacity < max_capacity) {
      // std::cerr << "min: " << min_capacity << ", max: " << max_capacity << "\n";
      int current_capacity = min_capacity + (max_capacity - min_capacity)/2;
      if (is_valid_capaciy(vessels, number_of_containers, current_capacity))
        max_capacity = current_capacity;
      else
        min_capacity = current_capacity + 1;
    }

    std::cout << min_capacity << '\n';
  }

  return 0;
}
