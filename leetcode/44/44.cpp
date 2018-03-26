#include <iostream>
#include <string>
#include <vector>

class Solution
{
  public:
    bool isMatch(const std::string &s, const std::string &p)
    {
      if (s.size() == 0)
      {
        for (const auto &c: p)
        {
          if (c != '*')
          {
            return false;
          }
        }

        return true;
      }

      if (p.size() == 0)
      {
        return false;
      }

      std::vector<std::vector<bool>> dp (p.size(), std::vector<bool> (s.size(), false));

      for (std::string::size_type i = 0, j = 0, count = 0; i < p.size(); i++)
      {
        if (p[i] == '*')
        {
        }
        else if (p[i] == '?' || p[i] == s[j])
        {
          count++;
        }
        else
        {
          count = 2;
        }

        dp[i][j] = (count <= 1);
      }

      for (std::string::size_type i = 0, j = 1; j < s.size(); j++)
      {
        dp[i][j] = (p[i] == '*');
      }

      for (std::string::size_type i = 1; i < p.size(); i++)
      {
        for (std::string::size_type j = 1; j < s.size(); j++)
        {
          if (p[i] == '*')
          {
            dp[i][j] = dp[i-1][j] | dp[i][j-1];
          }
          else if (p[i] == '?' || p[i] == s[j])
          {
            dp[i][j] = dp[i-1][j-1];
          }
          else
          {
            dp[i][j] = false;
          }
        }
      }

      return dp.back().back();
    }

    bool isMatchRecursive(const std::string &s, std::string::size_type i,
                          const std::string &p, std::string::size_type j)
    {
      if (i >= s.size() && j >= p.size())
      {
        return true;
      }
      else if (j >= p.size())
      {
        return false;
      }
      else if (i >= s.size() && p[j] != '*')
      {
        return false;
      }
      else if (p[j] == '?')
      {
        return isMatchRecursive(s, i+1, p, j+1);
      }
      else if (p[j] == '*')
      {
        for (std::string::size_type k = s.size(); k >= i && k <= s.size(); k--)
        {
          if (isMatchRecursive(s, k, p, j+1))
          {
            return true;
          }
        }

        return false;
      }
      else if (s[i] == p[j])
      {
        return isMatchRecursive(s, i+1, p, j+1);
      }
      else
      {
        return false;
      }
    }
};

int main(void)
{
  // std::string s = "aaaabaaaabbbbaabbbaabbaababbabbaaaababaaabbbbbbaabbbabababbaaabaabaaaaaabbaabbbbaababbababaabbbaababbbba";
  // std::string p = "*****b*aba***babaa*bbaba***a*aaba*b*aa**a*b**ba***a*a*";

  std::string s = "abbba";
  std::string p = "*a*a*";

  Solution sol;
  std::cout << sol.isMatch(s, p) << '\n';

  return 0;
}
