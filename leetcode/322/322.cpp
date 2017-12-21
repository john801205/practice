#include <climits>

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  public:
    int coinChange(vector<int>& coins, int amount) {
      vector<int> result (amount+1, INT_MAX);

      result[0] = 0;
      for (int i = 1; i <= amount; i++)
        for (auto &coin: coins)
          if (coin <= i && result[i - coin] != INT_MAX)
            result[i] = min(result[i], result[i - coin]+1);

      return result[amount] == INT_MAX ? -1 : result[amount];
    }
};

int main(void)
{
  int c[] = {216, 440, 325, 453, 232, 431}, amount = 8364;
  vector<int> coins (c, c + sizeof(c)/sizeof(int));

  Solution s;
  int q = s.coinChange(coins, amount);
  std::cout << q << std::endl;

  return 0;
}
