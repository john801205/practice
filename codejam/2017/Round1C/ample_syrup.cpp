#include <climits>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

#define PI 3.14159265358979323846

struct Pancake
{
  int R, H;

  Pancake(int R, int H): R(R), H(H) {}
};

bool comp(const Pancake &lft, const Pancake &rht)
{
  if (lft.R != rht.R)
  {
    return lft.R > rht.R;
  }
  else
  {
    return lft.H > rht.H;
  }
}

int main(void)
{
  std::cout << std::fixed << std::setprecision(9);

  int number_of_tests;
  std::cin >> number_of_tests;

  for (int test = 1; test <= number_of_tests; test++)
  {
    int N, K;
    std::cin >> N >> K;

    std::vector<Pancake> pancakes;
    std::vector<std::vector<double>> areas (2, std::vector<double> (K, 0));

    double max_area = 0.0;

    for (int i = 0; i < N; i++)
    {
      int R, H;
      std::cin >> R >> H;
      pancakes.emplace_back(R, H);
    }

    std::sort(std::begin(pancakes), std::end(pancakes), comp);

    for (int i = 0; i < N; i++)
    {

      areas[1][0] = PI * pancakes[i].R * pancakes[i].R + 2.0 * PI * pancakes[i].R * pancakes[i].H;
      // std::cerr << i << ' ' << pancakes[i].R << ' ' << pancakes[i].H << ' ' << areas[i][0] << '\n';

      double circle = 2.0 * PI * pancakes[i].R * pancakes[i].H;

      for (int k = 0; k+1 < K; k++)
      {
        if (areas[0][k] != 0 && areas[0][k] + circle > areas[1][k+1])
        {
          areas[1][k+1] = areas[0][k] + circle;
          // std::cerr << j << ' ' << areas[i][k+1] << '\n';
        }
      }

      for (int k = 0; k < K; k++)
      {
        areas[0][k] = std::max(areas[0][k], areas[1][k]);
        max_area = std::max(max_area, areas[0][k]);
      }
    }

    std::cout << "Case #" << test << ": " << max_area << "\n";
  }

  return 0;
}
