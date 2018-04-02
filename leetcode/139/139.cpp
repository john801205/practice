#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

class Solution
{
  public:
    bool wordBreak(const std::string s, const std::vector<std::string>& wordDict)
    {
      std::unordered_set<std::string> set    (std::begin(wordDict), std::end(wordDict));
      std::vector<std::vector<bool>>  exists (s.size(), std::vector<bool> (s.size(), false));
      std::vector<bool>               dp     (s.size()+1, false);

      for (std::string::size_type i = 0; i < s.size(); i++)
      {
        std::string word;

        for (std::string::size_type j = i; j < s.size(); j++)
        {
          word += s[j];

          if (set.find(word) != set.end())
          {
            exists[i][j] = true;
          }
        }
      }

      dp[0] = true;
      for (std::string::size_type i = 0; i < s.size(); i++)
      {
        for (std::string::size_type j = 0; j <= i; j++)
        {
          if (dp[j] && exists[j][i])
          {
            dp[i+1] = true;
            break;
          }
        }
      }

      return dp.back();
    }
};

int main(void)
{
  Solution s;
  assert(s.wordBreak("leetcode", std::vector<std::string> ({"leet","code"})));
  assert(s.wordBreak("leetleet", std::vector<std::string> ({"leet","code"})));
  assert(s.wordBreak("leetleet", std::vector<std::string> ({"code"})) == false);
  assert(s.wordBreak("leetleet", std::vector<std::string> ()) == false);

  std::cout << s.wordBreak("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"}) << '\n';
  return 0;
}
