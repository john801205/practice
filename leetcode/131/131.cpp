#include <cassert>
#include <iostream>
#include <string>
#include <vector>

class Solution
{
  public:
    std::vector<std::vector<std::string>> partition(const std::string s)
    {
      std::vector<std::vector<std::string>> result;
      std::vector<std::string> palindromes;
      dfs(s, palindromes, result);

      return result;
    }

    void dfs(const std::string                            s,
                   std::vector<std::string>              &palindromes,
                   std::vector<std::vector<std::string>> &result)
    {
      if (s.size() == 0)
      {
        result.emplace_back(palindromes);
        return;
      }

      for (std::string::size_type length = 1; length <= s.size(); length++)
      {
        std::string::size_type left = 0, right = length-1;

        while (left < right && s[left] == s[right])
        {
          left++;
          right--;
        }

        if (s[left] == s[right])
        {
          palindromes.emplace_back(s.substr(0, length));
          dfs(s.substr(length), palindromes, result);
          palindromes.pop_back();
        }
      }
    }
};

int main(void)
{
  Solution s;
  assert(s.partition("aab") == std::vector<std::vector<std::string>> ({{"a", "a", "b"}, {"aa", "b"}}));

  return 0;
}
