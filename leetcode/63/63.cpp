#include <iostream>
#include <vector>

class Solution
{
  public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>> &obstacleGrid)
    {
      if (obstacleGrid.size() == 0 || obstacleGrid[0].size() == 0)
      {
        return 0;
      }

      const auto m = obstacleGrid.size(), n = obstacleGrid[0].size();
      std::vector<std::vector<int>> dp (m+1, std::vector<int> (n+1, 0));

      dp[0][1] = 1;

      for(std::vector<std::vector<int>>::size_type i = 1; i < dp.size(); i++)
      {
        for (std::vector<int>::size_type j = 1; j < dp[i].size(); j++)
        {
          if (obstacleGrid[i-1][j-1] != 1)
          {
            // empty
            dp[i][j] = dp[i][j-1] + dp[i-1][j];
          }
        }
      }

      return dp[m][n];
    }
};

int main(void)
{
  return 0;
}
