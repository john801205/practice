#include <cassert>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

class Solution
{
  public:
    std::vector<int> topKFrequent(const std::vector<int>& nums, const int k)
    {
      std::priority_queue<std::pair<int,int>> queue;
      std::unordered_map<int, int> map;
      std::vector<int> result(k);

      for (const auto &num: nums)
        map[num]++;

      for (const auto itr: map)
        queue.emplace(itr.second, -itr.first);

      for (int i = 0; i < k; i++)
      {
        result[i] = -queue.top().second;
        queue.pop();
      }

      return result;
    }
};

int main()
{
  Solution s;
  assert(s.topKFrequent({2,2,3,2,2,1,1,1,1}, 2) == std::vector<int> ({1,2}));
  return 0;
}
