#include <cassert>
#include <climits>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int calculateMinimumHP(const std::vector<std::vector<int>> &dungeon)
    {
      std::vector<int> dp (dungeon[0].size()+1, INT_MAX);

      dp[dungeon[0].size()-1] = 1;
      for (std::vector<int>::size_type i = dungeon.size(); i-- > 0; )
      {
        for (std::vector<int>::size_type j = dungeon[i].size(); j-- > 0; )
        {
          dp[j] = std::min(dp[j], dp[j+1]) - dungeon[i][j];
          dp[j] = std::max(1, dp[j]);
        }
      }

      return dp.front();
    }
};

int main(void)
{
  Solution s;
  assert(s.calculateMinimumHP({{-2,-3,3},{-5,-10,1},{10,30,-5}}) == 7);
  assert(s.calculateMinimumHP({{-2,-3,3,1,-1},{-5,-10,1,-2,-3},{10,30,-5,-5,-4}}) == 8);
  assert(s.calculateMinimumHP({{-2,-3,3,1,-1},{-5,-10,1,-2,-3},{10,30,-5,-5,-4},{-10,-2,-3,1,0}}) == 8);
  assert(s.calculateMinimumHP({{-2,-3,3,1,-1},{-5,-10,1,-2,-3},{10,30,-5,-5,-4},{-10,-2,-3,-21,0}}) == 8);
  return 0;
}
