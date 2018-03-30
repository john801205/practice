#include <cassert>
#include <iostream>
#include <string>
#include <vector>

class Solution
{
  public:
    std::string shortestPalindrome(const std::string s)
    {
      const std::string reversed (s.rbegin(), s.rend());
      const std::vector<std::string::size_type> nexts = makeNext(s);

      std::string::size_type i, j;
      for (i = 0, j = 0; i < reversed.size(); )
      {
        if (reversed[i] == s[j])
        {
          i++;
          j++;
        }
        else
        {
          if (j == 0)
          {
            i++;
          }
          else
          {
            j = nexts[j-1];
          }
        }
      }

      return reversed + s.substr(j);
    }

    std::vector<std::string::size_type> makeNext(const std::string s)
    {
      std::vector<std::string::size_type> nexts (s.size(), 0);

      for (std::string::size_type i = 1, j = 0; i < s.size(); )
      {
        if (s[i] == s[j])
        {
          nexts[i] = j+1;
          i++;
          j++;
        }
        else
        {
          if (j == 0)
          {
            nexts[i] = 0;
            i++;
          }
          else
          {
            j = nexts[j-1];
          }
        }
      }

      return nexts;
    }
};

int main(void)
{
  Solution s;
  assert(s.shortestPalindrome("aacecaaa") == "aaacecaaa");
  assert(s.shortestPalindrome("abcd") == "dcbabcd");
  assert(s.shortestPalindrome("") == "");
  assert(s.shortestPalindrome("a") == "a");
  assert(s.shortestPalindrome("aa") == "aa");
  assert(s.shortestPalindrome("aba") == "aba");
  assert(s.shortestPalindrome("abac") == "cabac");
  return 0;
}
