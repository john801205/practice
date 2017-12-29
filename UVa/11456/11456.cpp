#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

std::vector<int> longest_increasing_subsequece(const std::vector<int>& numbers)
{
  if (numbers.size() == 0)
    return std::vector<int> ();

  std::vector<int> LIS (numbers.size());
  std::vector<int> results;

  LIS[0] = 1;
  results.push_back(numbers.front());

  for (std::vector<int>::size_type i = 1; i < numbers.size(); i++) {
    if (numbers[i] > results.back()) {
      LIS[i] = results.size() + 1;
      results.push_back(numbers[i]);
    } else {
      std::vector<int>::size_type left = 0,
                                  right = results.size() - 1,
                                  middle;

      while (left < right) {
        middle = left + (right - left) / 2;
        if (numbers[i] <= results[middle])
          right = middle;
        else
          left = middle + 1;
      }

      LIS[i] = left + 1;
      results[left] = numbers[i];
    }
  }

  return LIS;
}

std::vector<int> longest_decreasing_subsequece(const std::vector<int>& numbers)
{
  if (numbers.size() == 0)
    return std::vector<int> ();

  std::vector<int> LDS (numbers.size());
  std::vector<int> results;

  LDS[0] = 1;
  results.push_back(numbers.front());

  for (std::vector<int>::size_type i = 1; i < numbers.size(); i++) {
    if (numbers[i] < results.back()) {
      LDS[i] = results.size() + 1;
      results.push_back(numbers[i]);
    } else {
      std::vector<int>::size_type left = 0,
                                  right = results.size() - 1,
                                  middle;

      while (left < right) {
        middle = left + (right - left) / 2;
        if (numbers[i] >= results[middle])
          right = middle;
        else
          left = middle + 1;
      }

      LDS[i] = left + 1;
      results[left] = numbers[i];
    }
  }

  return LDS;
}
int main(void)
{
  int number_of_cases;

  while (std::cin >> number_of_cases) {
    for (int case_ = 0; case_ < number_of_cases; case_++) {
      int number_of_cars;
      std::vector<int> cars;

      std::cin >> number_of_cars;
      for (int i = 0, car; i < number_of_cars; i++) {
        std::cin >> car;
        cars.push_back(car);
      }

      std::reverse(cars.begin(), cars.end());
      std::vector<int> LIS = longest_increasing_subsequece(cars),
                       LDS = longest_decreasing_subsequece(cars);

      int max = 0;
      for (std::vector<int>::size_type i = 0; i < cars.size(); i++)
        if (max < LIS[i] + LDS[i] - 1)
          max = LIS[i] + LDS[i] - 1;

      std::cout << max << '\n';
    }
  }

  return 0;
}
