#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

class Solution
{
  public:
    int longestConsecutive(const std::vector<int> &nums)
    {
      std::vector<std::vector<int>::size_type> parents (nums.size());
      std::vector<std::vector<int>::size_type> ranks   (nums.size(), 0);
      std::vector<int> sizes (nums.size(), 1);
      std::unordered_map<int, std::vector<int>::size_type> maps;
      int longest = nums.size() == 0 ? 0 : 1;

      for (std::vector<int>::size_type i = 0; i < parents.size(); i++)
      {
        parents[i] = i;
      }

      for (std::vector<int>::size_type i = 0; i < nums.size(); i++)
      {
        maps[nums[i]] = i;
      }

      for (const auto &num: nums)
      {
        if (maps.find(num + 1) == maps.end())
        {
          continue;
        }

        std::vector<int>::size_type pi = findRoot(parents, maps[num]);
        std::vector<int>::size_type pj = findRoot(parents, maps[num+1]);

        if (pi == pj)
        {
          continue;
        }

        longest = std::max(longest, sizes[pi] + sizes[pj]);

        if (ranks[pi] > ranks[pj])
        {
          parents[pj] = pi;
          sizes[pi] += sizes[pj];
        }
        else if (ranks[pi] < ranks[pj])
        {
          parents[pi] = pj;
          sizes[pj] += sizes[pi];
        }
        else
        {
          parents[pi] = pj;
          ranks[pj] += 1;
          sizes[pj] += sizes[pi];
        }
      }

      return longest;
    }

    std::vector<int>::size_type findRoot(std::vector<std::vector<int>::size_type> &parents,
                                         std::vector<int>::size_type               index)
    {
      if (parents[index] != index)
      {
        auto root = findRoot(parents, parents[index]);
        parents[index] = root;
      }

      return parents[index];
    }
};

int main(void)
{
  Solution s;
  assert(s.longestConsecutive({100, 4, 200, 1, 3, 2}) == 4);
  assert(s.longestConsecutive({100,4,200,1,3,2, 3, 101, 102, 5, 99, 98}) == 5);
  assert(s.longestConsecutive({}) == 0);
  assert(s.longestConsecutive({1}) == 1);
  assert(s.longestConsecutive({1, 3, 5}) == 1);
  return 0;
}
