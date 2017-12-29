#include <algorithm>
#include <iostream>
#include <vector>

struct Building {
  int height, width;
};

template <typename T>
int longest_subsequences(std::vector<Building>& buildings, T comp)
{
  if (buildings.size() == 0)
    return 0;

  std::vector<int> result (buildings.size(), 0);

  for (std::vector<Building>::size_type i = 0; i < buildings.size(); i++) {
    result[i] = buildings[i].width;

    for (std::vector<Building>::size_type j = 0; j < i; j++) {
      if (comp(buildings[i].height, buildings[j].height)
          && result[j] + buildings[i].width > result[i])
        result[i] = result[j] + buildings[i].width;
    }
  }

  return *max_element(result.begin(), result.end());
}

int main(void)
{
  int number_of_cases;

  while (std::cin >> number_of_cases) {
    for (int case_ = 1; case_ <= number_of_cases; case_++) {
      int number_of_buildings;
      std::cin >> number_of_buildings;

      std::vector<Building> buildings (number_of_buildings);
      for (int i = 0; i < number_of_buildings; i++)
        std::cin >> buildings[i].height;
      for (int i = 0; i < number_of_buildings; i++)
        std::cin >> buildings[i].width;

      int increasing = longest_subsequences(buildings, std::greater<int>()),
          decreasing = longest_subsequences(buildings, std::less<int>());

      std::cout << "Case " << case_ << ". ";
      if (increasing >= decreasing)
        std::cout << "Increasing (" << increasing << "). "
                  << "Decreasing (" << decreasing << ").\n";
      else
        std::cout << "Decreasing (" << decreasing << "). "
                  << "Increasing (" << increasing << ").\n";
    }
  }

  return 0;
}
