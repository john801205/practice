#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

struct Node
{
  int profit, capital;

  Node(int profit, int capital): profit(profit), capital(capital) {}

  Node(const Node &x): profit(x.profit), capital(x.capital) {}
};

bool operator<(const Node &lhs, const Node &rhs)
{
  return lhs.capital > rhs.capital;
}

class Solution
{
  public:
    int findMaximizedCapital(const int               k,
                             const int               W,
                             const std::vector<int> &Profits,
                             const std::vector<int> &Capital)
    {
      std::priority_queue<Node> over;
      std::priority_queue<int> enough;

      for (std::vector<int>::size_type i = 0; i < Profits.size(); i++)
          over.emplace(Profits[i], Capital[i]);

      int earned = W;
      for (int i = 0; i < k; i++)
      {
        while (!over.empty() && over.top().capital <= earned)
        {
          enough.emplace(over.top().profit);
          over.pop();
        }

        if (enough.empty() || enough.top() == 0)
          break;

        const auto profit = enough.top();
        enough.pop();

        earned += profit;
      }

      return earned;
    }
};

int main()
{
  Solution s;
  assert(s.findMaximizedCapital(2, 0, {1,2,3}, {0,1,1}) == 4);
  assert(s.findMaximizedCapital(2, 1, {1,2,3}, {0,1,1}) == 6);
  assert(s.findMaximizedCapital(3, 1, {1,2,3}, {0,1,1}) == 7);
  assert(s.findMaximizedCapital(3, 1, {1,2,3,7}, {0,1,1,4}) == 13);
  assert(s.findMaximizedCapital(2, 1, {1,2,3,7}, {0,1,1,4}) == 11);
  assert(s.findMaximizedCapital(2, 0, {1,2,3,7}, {0,1,1,4}) == 4);
  return 0;
}
