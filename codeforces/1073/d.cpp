#include <iostream>
#include <vector>

int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int                   number_of_booths;
  unsigned long long    burles;
  std::vector<unsigned> prices;

  std::cin >> number_of_booths;
  std::cin >> burles;

  prices.resize(number_of_booths);
  for (int i = 0; i < number_of_booths; i++)
  {
    std::cin >> prices[i];
  }

  unsigned long long candies = 0;

  while (true)
  {
    unsigned long long round_prices = 0;
    unsigned long long round_candies = 0;

    for (const auto price: prices)
    {
      if (round_prices+price <= burles)
      {
        round_prices += price;
        round_candies += 1;
      }
    }

    if (round_candies == 0)
      break;

    candies += (burles / round_prices) * round_candies;
    burles %= round_prices;
  }

  std::cout << candies << '\n';

  return 0;
}
