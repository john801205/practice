#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int maxProfit(const std::vector<int> &prices, int fee)
    {
      if (prices.size() < 2)
        return 0;

      int hold = -prices[0], empty = 0;

      for (std::vector<int>::size_type i = 1; i < prices.size(); i++)
      {
        empty = std::max(empty, hold + prices[i] - fee);
        hold = std::max(hold, empty - prices[i]);
      }

      return empty;
    }
};

int main()
{
  Solution s;
  assert(s.maxProfit({1, 3, 2, 8, 4, 9}, 2) == 8);
  return 0;
}
