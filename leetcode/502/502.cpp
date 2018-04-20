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
  if (lhs.profit != rhs.profit)
    return lhs.profit < rhs.profit;
  else
    return lhs.capital < rhs.capital;
}

class Compare
{
  public:
    bool operator() (const Node &lhs, const Node &rhs)
    {
      return rhs.capital < lhs.capital;
    }
};

class Solution
{
  public:
    int findMaximizedCapital(const int               k,
                             const int               W,
                             const std::vector<int> &Profits,
                             const std::vector<int> &Capital)
    {
      std::priority_queue<Node> enough;
      std::priority_queue<Node, std::vector<Node>, Compare> over;

      for (std::vector<int>::size_type i = 0; i < Profits.size(); i++)
          enough.emplace(Profits[i], Capital[i]);

      int earned = W;
      for (int i = 0; i < k; i++)
      {
        while (!over.empty() && over.top().capital <= earned)
        {
          enough.emplace(over.top());
          over.pop();
        }

        while (!enough.empty() && enough.top().capital > earned)
        {
          over.emplace(enough.top());
          enough.pop();
        }

        if (enough.empty())
          break;

        const auto project = enough.top();
        enough.pop();

        earned += project.profit;
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
