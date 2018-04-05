#include <cassert>
#include <climits>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int maxProfit(int k, const std::vector<int> &prices)
    {
      if (k*2 >= prices.size())
      {
        int profit = 0;
        for (std::vector<int>::size_type i = 1; i < prices.size(); i++)
        {
          profit += std::max(0, prices[i] - prices[i-1]);
        }

        return profit;
      }

      std::vector<int> holds    (k+1, INT_MIN);
      std::vector<int> releases (k+1, 0);

      for (std::vector<int>::size_type i = 0; i < prices.size(); i++)
      {
        for (std::vector<int>::size_type j = k; j > 0; j--)
        {
          releases[j] = std::max(releases[j], holds[j] + prices[i]);
          holds[j] = std::max(holds[j], releases[j-1] - prices[i]);
        }
      }

      return releases.back();
    }
};

int main(void)
{
  Solution s;
  assert(s.maxProfit(2, {}) == 0);
  assert(s.maxProfit(2, {1,2,3,4,5}) == 4);
  assert(s.maxProfit(2, {1,2,3,4,5,1,6}) == 9);
  assert(s.maxProfit(2, {1,2,3,4,5,1,6,1,2}) == 9);
  assert(s.maxProfit(2, {1,2,3,4,5,1,6,1,2,1,8}) == 12);
  assert(s.maxProfit(2, {6,1,3,2,4,7}) == 7);
  assert(s.maxProfit(2, {6,1,3,2,4,7,2}) == 7);
  assert(s.maxProfit(2, {6,1,3,2,4,7,2,3}) == 7);
  assert(s.maxProfit(2, {6,1,4,2,4,7,2,3}) == 8);
  assert(s.maxProfit(2, {6,1,4,2,5,7,2,3}) == 8);
  return 0;
}
