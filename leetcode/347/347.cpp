#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

class Solution
{
  public:
    std::vector<int> topKFrequent(const std::vector<int>& nums, const int k)
    {
      std::vector<std::vector<int>> buckets (nums.size()+1, std::vector<int> ());
      std::unordered_map<int, int>  map;
      std::vector<int>              result (k);

      for (const auto &num: nums)
        map[num]++;

      for (const auto itr: map)
        buckets[itr.second].emplace_back(itr.first);

      std::vector<int>::size_type i = 0;
      for (auto itr = buckets.rbegin(); itr != buckets.rend(); itr++)
      {
        for (const auto &num: *itr)
        {
          result[i] = num;
          i++;

          if (i == result.size())
            break;
        }
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
