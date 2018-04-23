#include <cassert>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

class Solution
{
  public:
    std::vector<std::pair<int, int>>
    getSkyline(const std::vector<std::vector<int>> &buildings)
    {
      std::unordered_map<int, std::vector<int>> added, deleted;
      std::set<int> range;
      std::multiset<int> heights;

      for (const auto &building: buildings)
      {
        added[building[0]].emplace_back(building[2]);
        deleted[building[1]].emplace_back(building[2]);
        range.emplace(building[0]);
        range.emplace(building[1]);
      }

      std::vector<std::pair<int,int>> result;
      int prev = 0;

      for (const auto &x: range)
      {
        for (const auto &h: added[x])
          heights.emplace(h);

        for (const auto &h: deleted[x])
        {
          auto itr = heights.find(h);
          if (itr != heights.end())
            heights.erase(itr);
        }

        const auto max = heights.empty() ? 0 : *std::prev(std::end(heights));
        if (max != prev)
          result.emplace_back(x, max);

        prev = max;
      }

      return result;
    }
};

int main()
{
  Solution s;
  assert(s.getSkyline({{2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}}) == (std::vector<std::pair<int,int>> ({{2,10},{3,15},{7,12},{12,0},{15,10},{20,8},{24,0}})));
  assert(s.getSkyline({{0,2,3},{2,5,3}}) == (std::vector<std::pair<int,int>> ({{0,3},{5,0}})));
  return 0;
}
