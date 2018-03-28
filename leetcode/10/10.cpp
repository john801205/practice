#include <iostream>
#include <string>
#include <vector>

class Solution
{
  public:
    bool isMatch(const std::string &s, const std::string &p)
    {
      std::vector<std::vector<bool>> dp (p.size()+1, std::vector<bool> (s.size()+1, false));

      // empty s and empty p
      dp[0][0] = true;

      // non-empty s and empty p
      for (std::string::size_type j = 1; j <= s.size(); j++)
      {
        dp[0][j] = false;
      }

      // empty s and non-empty p
      for (std::string::size_type i = 1, count = 0; i <= p.size(); i++)
      {
        if (p[i-1] == '*')
        {
          count--;
        }
        else
        {
          count++;
        }

        dp[i][0] = (count == 0);
      }

      for (std::string::size_type i = 1; i <= p.size(); i++)
      {
        for (std::string::size_type j = 1; j <= s.size(); j++)
        {
          if (p[i-1] == '*')
          {
            dp[i][j] = (((s[j-1] == p[i-2] || p[i-2] == '.') && dp[i][j-1]) || (i > 1 && dp[i-2][j]));
          }
          else if (p[i-1] == '.' || p[i-1] == s[j-1])
          {
            dp[i][j] = dp[i-1][j-1];
          }
          else
          {
            dp[i][j] = false;
          }
        }
      }

      std::cerr << "  " << s << '\n';

      for (std::string::size_type i = 0; i <= p.size(); i++)
      {
        if (i != 0)
          std::cerr << p[i-1];
        else
          std::cerr << ' ';

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
