#include <cassert>
#include <climits>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int maxProfit(const std::vector<int> &prices)
    {
      std::vector<int> profits (prices.size()+1, 0);
      int min_price = INT_MAX;
      int max_price = INT_MIN;
      int max_profit = 0;

      for (std::vector<int>::size_type i = 0; i < prices.size(); i++)
      {
        min_price = std::min(min_price, prices[i]);
        profits[i+1] = std::max(profits[i], prices[i] - min_price);
      }

      for (std::vector<int>::size_type i = prices.size(); i-- > 0; )
      {
        max_price = std::max(max_price, prices[i]);
        max_profit = std::max(max_profit, max_price - prices[i] + profits[i]);
      }

      return max_profit;
    }
};

int main(void)
{
  Solution s;
  assert(s.maxProfit({}) == 0);
  assert(s.maxProfit({1}) == 0);
  assert(s.maxProfit({1,0,3,4,0,3,4}) == 8);
  assert(s.maxProfit({1,0,3,4,0,3,4,0,3,4}) == 8);
  assert(s.maxProfit({1,8,9,2,1,2,3,1,8}) == 15);
  assert(s.maxProfit({1,8,9,2,1,2,3,1,8,9,2,3,7}) == 16);
  assert(s.maxProfit({6,1,3,2,4,7}) == 7);

  return 0;
}
