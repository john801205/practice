#include <iostream>

int main(void)
{
  int number_of_test_cases;

  while (std::cin >> number_of_test_cases)
  {
    for (int case_ = 0; case_ < number_of_test_cases; case_++)
    {
      int types_of_coins, cur_coin, coin_sum, number_of_coins;

      std::cin >> types_of_coins >> cur_coin;

      coin_sum = cur_coin;
      number_of_coins = 1;
      for (int i = 1; i < types_of_coins; i++)
      {
        int prev_coin = cur_coin;

        std::cin >> cur_coin;
        if (coin_sum >= cur_coin)
        {
          coin_sum -= prev_coin;
          number_of_coins--;
        }

        coin_sum += cur_coin;
        number_of_coins++;
      }

      std::cout << number_of_coins << '\n';
    }
  }

  return 0;
}
