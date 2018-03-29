#include <cassert>

#include <iostream>
#include <string>
#include <vector>

class Solution
{
  public:
    bool isInterleave(const std::string &s1,
                      const std::string &s2,
                      const std::string &s3)
    {
      if (s1.size() + s2.size() != s3.size())
      {
        return false;
      }

      // dp[i][j] represents whether s1[0,i) and s2[0,j) forms s3[0,i+j+1)
      std::vector<bool> dp (s2.size()+1, false);

      // empty s1, empty s2
      dp[0] = true;

      // empty s1, non-empty s2
      for (std::string::size_type j = 0; j < s2.size(); j++)
      {
        dp[j+1] = (dp[j] && s2[j] == s3[j]);
      }

      for (std::string::size_type i = 0; i < s1.size(); i++)
      {
        dp[0] = (dp[0] && s1[i] == s3[i]);

        for (std::string::size_type j = 0; j < s2.size(); j++)
        {
          dp[j+1] = (s3[i+j+1] == s1[i] && dp[j+1]) || (s3[i+j+1] == s2[j] && dp[j]);
        }
      }

      return dp.back();
    }
};

int main(void)
{
  Solution s;
  assert(s.isInterleave("aabcc", "dbbca", "aadbbcbcac") == true);
  assert(s.isInterleave("aabcc", "dbbca", "aadbbbaccc") == false);
  assert(s.isInterleave("", "", "") == true);
  assert(s.isInterleave("", "", "aaaa") == false);
  assert(s.isInterleave("ab", "ab", "aabb") == true);
  return 0;
}
