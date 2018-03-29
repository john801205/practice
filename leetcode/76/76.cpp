#include <cassert>

#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>

class Solution
{
  public:
    std::string minWindow(const std::string s, const std::string t)
    {
      std::string result;
      std::string::size_type result_size = std::numeric_limits<std::string::size_type>::max();
      std::string::size_type start = 0, count = 0;
      std::unordered_map<char, int> maps;

      for (const auto &c: t)
      {
        maps[c]++;
      }

      for (std::string::size_type i = 0; i < s.size(); i++)
      {
        auto search = maps.find(s[i]);

        if (search == maps.end())
        {
          continue;
        }

        if (count == 0)
        {
          start = i;
        }

        if (maps[s[i]] > 0)
        {
          count++;
        }

        maps[s[i]]--;

        if (count == t.size())
        {
          for (std::string::size_type j = start; j <= i; j++)
          {
            if (maps.find(s[j]) == maps.end())
            {
              continue;
            }

            if (count+1 == t.size())
            {
              start = j;
              break;
            }

            maps[s[j]]++;

            if (maps[s[j]] > 0)
            {
              count--;
            }

            if (i-j+1 < result_size)
            {
              result = s.substr(j, i-j+1);
              result_size = i-j+1;
            }
          }
        }
      }

      return result;
    }
};

int main(void)
{
  Solution s;
  assert(s.minWindow("ADOBECODEBANC", "ABC") == "BANC");
  assert(s.minWindow("A", "A") == "A");
  assert(s.minWindow("AAAA", "B") == "");
  assert(s.minWindow("abcdeabcdabeedbade", "abe") == "eab");
  assert(s.minWindow("abcdeabcdabeedbade", "abed") == "deab");
  assert(s.minWindow("aa", "aa") == "aa");
  assert(s.minWindow("acdebcadeab", "aab") == "adeab");
  assert(s.minWindow("acacacacdebcadeab", "aab") == "adeab");
  assert(s.minWindow("bba", "ab") == "ba");

  std::cout << "Final: " << s.minWindow("bba", "abb") << '\n';

  return 0;
}
