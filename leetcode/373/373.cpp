#include <cassert>
#include <iostream>
#include <vector>
#include <queue>

class Solution
{
  public:
    std::vector<std::pair<int, int>>
    kSmallestPairs(const std::vector<int> &nums1,
                   const std::vector<int> &nums2,
                         int               k)
    {
      k = std::min<int>(k, nums1.size()*nums2.size());
      if (k == 0)
        return {};

      std::vector<std::pair<int, int>> results;
      std::priority_queue<std::pair<int, std::vector<int>::size_type>> queue;
      std::vector<std::vector<int>::size_type> indexes (nums1.size(), 0);

      for (std::vector<int>::size_type i = 0; i < nums1.size(); i++)
        queue.emplace(-(nums1[i] + nums2[0]), i);

      int count = 0;

      while (count < k)
      {
        auto index = queue.top().second;
        queue.pop();

        results.emplace_back(nums1[index], nums2[indexes[index]]);
        count++;

        if (indexes[index] + 1 < nums2.size())
        {
          indexes[index]++;

          queue.emplace(-(nums1[index] + nums2[indexes[index]]), index);
        }
      }

      return results;
    }
};

int main()
{
  Solution s;
  auto r = s.kSmallestPairs({1,1,2}, {1,2,3}, 2);

  for (const auto &v: r)
    std::cerr << v.first << '\t' << v.second << '\n';

  return 0;
}
