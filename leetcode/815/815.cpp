#include <cassert>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution
{
  public:
    int numBusesToDestination(
        const std::vector<std::vector<int>> &routes,
        const int S, const int T)
    {
      if (S == T)
        return 0;

      std::unordered_map<int, std::unordered_set<int>> indexes;
      for (std::vector<int>::size_type i = 0; i < routes.size(); i++)
      {
        for (const auto &stop: routes[i])
        {
          indexes[stop].emplace(i);
        }
      }

      std::vector<std::unordered_set<int>> edges(routes.size());
      std::unordered_map<int, bool> targets;
      for (std::vector<int>::size_type i = 0; i < routes.size(); i++)
      {
        for (const auto &stop: routes[i])
        {
          edges[i].insert(indexes[stop].begin(), indexes[stop].end());

          if (stop == T)
            targets[i] = true;
        }
      }

      std::queue<int> queue;
      std::vector<int> depth(routes.size(), 0);

      for (const auto &i: indexes[S])
      {
        queue.emplace(i);
        depth[i] = 1;
      }

      while (!queue.empty())
      {
        std::vector<int>::size_type cur = queue.front();
        queue.pop();

        if (targets[cur])
          return depth[cur];

        for (const auto &i: edges[cur])
        {
          if (depth[i] == 0)
          {
            queue.emplace(i);
            depth[i] = depth[cur] + 1;
          }
        }
      }

      return -1;
    }
};

int main()
{
  Solution s;
  assert(s.numBusesToDestination({{1, 2, 7}, {3, 6, 7}}, 1, 6) == 2);
  assert(s.numBusesToDestination({{1, 2, 7}, {3, 6, 2}}, 1, 6) == 2);
  return 0;
}
