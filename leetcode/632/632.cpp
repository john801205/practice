#include <cassert>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

class Solution
{
  public:
    std::vector<int> smallestRange(const std::vector<std::vector<int>> &nums)
    {
      std::vector<std::vector<int>::size_type> indexes (nums.size(), 0);
      std::multiset<int> current;
      std::priority_queue<std::pair<int, std::vector<std::vector<int>>::size_type>> queue;

      for (std::vector<std::vector<int>>::size_type i = 0; i < nums.size(); i++)
      {
        queue.emplace(-nums[i][0], i);
        current.emplace(nums[i][0]);
      }

      std::vector<int> range = {*current.begin(), *current.rbegin()};

      while (true)
      {
        const auto num = -queue.top().first;
        const auto i = queue.top().second;
        queue.pop();

        if (indexes[i] + 1 == nums[i].size())
          break;

        current.erase(current.find(num));
        indexes[i]++;
        queue.emplace(-nums[i][indexes[i]], i);
        current.emplace(nums[i][indexes[i]]);

        std::vector<int> temp = {*current.begin(), *current.rbegin()};
        if (temp[1] - temp[0] < range[1] - range[0])
          range = temp;
      }

      return range;
    }
};

int main()
{
  Solution s;
  assert(s.smallestRange({{4,10,15,24,26},{0,9,12,20},{5,18,22,30}}) == std::vector<int> ({20,24}));
  return 0;
}
