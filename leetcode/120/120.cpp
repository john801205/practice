#include <cassert>
#include <climits>
#include <algorithm>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int minimumTotal(const std::vector<std::vector<int>> &triangle)
    {
      std::vector<int> dp (triangle.back());

      for (std::vector<int>::size_type i = triangle.size()-1; i-- > 0; )
        for (std::vector<int>::size_type j = 0; j < triangle[i].size(); j++)
          dp[j] = triangle[i][j] + std::min(dp[j], dp[j+1]);

      return dp[0];
    }
};

int main()
{
  Solution s;
  assert(s.minimumTotal({{2},{3,4},{6,5,7},{4,1,8,3}}) == 11);
  assert(s.minimumTotal({{2},{3,4},{6,5,7},{-4,1,8,3}}) == 7);
  assert(s.minimumTotal({{2},{3,4},{6,5,7},{-4,1,-8,3}}) == 2);
  return 0;
}
