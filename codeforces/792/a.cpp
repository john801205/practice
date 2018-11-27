#include <climits>

#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int number_of_cities;
  std::cin >> number_of_cities;

  std::vector<int> cities(number_of_cities);
  for (int i = 0; i < number_of_cities; i++)
  {
    std::cin >> cities[i];
  }

  std::sort(std::begin(cities), std::end(cities));

  int minimum_distance = INT_MAX;
  int pairs            = 0;

  for (int i = 1; i < number_of_cities; i++)
  {
    int distance = cities[i] - cities[i-1];
    if (distance < minimum_distance)
    {
      minimum_distance = distance;
      pairs = 1;
    }
    else if (distance == minimum_distance)
    {
      pairs += 1;
    }
  }

  std::cout << minimum_distance << ' ' << pairs << '\n';

  return 0;
}
