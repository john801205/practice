#include <iostream>
#include <string>
#include <vector>

class Solution
{
  public:
    int minDistance(const std::string word1, const std::string word2)
    {
      std::vector<int> dp (word2.size()+1, 0);

      for (std::string::size_type i = 1; i <= word2.size(); i++)
      {
        dp[i] = i;
      }

      for (std::string::size_type i = 1; i <= word1.size(); i++)
      {
        int prev = dp[0];
        dp[0] = i;

        for (std::string::size_type j = 1; j <= word2.size(); j++)
        {
          int temp = dp[j];

          if (word1[i-1] == word2[j-1])
          {
            dp[j] = prev;
          }
          else
          {
            dp[j] = std::min(prev, std::min(dp[j-1], dp[j])) + 1;
          }

          prev = temp;
        }
      }

      return dp.back();
    }
};

int main(void)
{
  return 0;
}
