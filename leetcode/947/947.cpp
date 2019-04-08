#include <cassert>
#include <iostream>
#include <unordered_set>
#include <vector>

class Solution
{
  public:
    int removeStones(const std::vector<std::vector<int>> &stones)
    {
      std::vector<int> parents(stones.size());

      for (std::vector<int>::size_type i = 0; i < parents.size(); i++)
        parents[i] = i;

      for (std::vector<int>::size_type i = 0; i < stones.size(); i++)
      {
        for (std::vector<int>::size_type j = i+1; j < stones.size(); j++)
        {
          if (stones[i][0] != stones[j][0] && stones[i][1] != stones[j][1])
            continue;

          unionn(parents, i, j);
        }
      }

      int count = 0;
      for (std::vector<int>::size_type i = 0; i < stones.size(); i++)
        if (parents[i] != i)
          count++;

      return count;
    }

    int find(std::vector<int> &parents, int idx)
    {
      if (parents[idx] != idx)
        parents[idx] = find(parents, parents[idx]);

      return parents[idx];
    }

    void unionn(std::vector<int> &parents, int idx, int idx2)
    {
      int p1 = find(parents, idx);
      int p2 = find(parents, idx2);
      parents[p2] = p1;
    }
};

int main()
{
  Solution s;
  assert(s.removeStones({{0, 0}, {0, 1}, {1, 0}, {1, 2}, {2, 1}, {2, 2}}) == 5);
  assert(s.removeStones({{0, 0}, {0, 2}, {2, 0}, {2, 2}, {1, 1}}) == 3);
  assert(s.removeStones({{0, 0}}) == 0);
  return 0;
}
