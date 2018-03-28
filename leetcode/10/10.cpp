#include <iostream>
#include <string>
#include <vector>

class Solution
{
  public:
    bool isMatch(const std::string &s, const std::string &p)
    {
      if (s.size() == 0 && p.size() == 0)
      {
        return true;
      }
      else if (p.size() == 0)
      {
        return false;
      }
      else if (s.size() == 0)
      {
        std::string::size_type count = 0;

        for (std::string::size_type i = 0; i < p.size(); i++)
        {
          if (p[i] == '*')
            count--;
          else
            count++;
        }

        return count == 0;
      }

      std::vector<std::vector<bool>> dp (p.size(), std::vector<bool> (s.size()));

      for (std::string::size_type j = 1; j < s.size(); j++)
      {
        dp[0][j] = false;
      }

      for (std::string::size_type i = 0, count = 0; i < p.size(); i++)
      {
        if (p[i] == '*')
        {
          if (i >= 2) dp[i][0] = dp[i-1][0] || dp[i-2][0];
          else if (i >= 1) dp[i][0] = dp[i-1][0];
          count--;
        }
        else if (p[i] == '.' || p[i] == s[0])
        {
          dp[i][0] = count == 0;
          count++;
        }
        else
        {
          dp[i][0] = false;
          count++;
        }
      }

      for (std::string::size_type i = 1; i < p.size(); i++)
      {
        for (std::string::size_type j = 1; j < s.size(); j++)
        {
          if (p[i] == '*')
          {
            if (p[i-1] == '.')
            {
              dp[i][j] = dp[i][j-1] || (i > 1 && dp[i-2][j]);
            }
            else
            {
              dp[i][j] = ((s[j] == p[i-1] && dp[i][j-1]) || (i > 1 && dp[i-2][j]));
            }
          }
          else if (p[i] == '.' || p[i] == s[j])
          {
            dp[i][j] = dp[i-1][j-1];
          }
          else
          {
            dp[i][j] = false;
          }
        }
      }

      std::cerr << ' ' << s << '\n';

      for (std::string::size_type i = 0; i < p.size(); i++)
      {
        std::cerr << p[i];

        for (const  auto &v: dp[i])
          std::cerr << v ;
        std::cerr << '\n';
      }

      return dp.back().back();
    }
};

int main(void)
{
  std::string s, p;

  while (std::cin >> s >> p)
  {
    Solution sol;
    std::cout << sol.isMatch(s, p) << '\n';
  }

  return 0;
}
