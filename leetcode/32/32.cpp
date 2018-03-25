#include <iostream>
#include <string>
#include <vector>

class Solution
{
  public:
    int longestValidParentheses(const std::string &s)
    {
      std::vector<std::string::size_type> lengths (s.size(), 0);
      std::string::size_type longest = 0;

      for (std::string::size_type i = 0; i < s.size(); i++)
      {
        if (i == 0 || s[i] == '(')
        {
          continue;
        }

        std::string::size_type prev = i - 1, length = 0, valid_length = 0;
        bool matched = false;

        while (prev < s.size())
        {
          if (!matched && s[prev] == '(')
          {
            matched = true;
            length += valid_length + 2;
            valid_length = 0;
            prev--;
          }
          else if (s[prev] == ')' && lengths[prev] != 0)
          {
            valid_length += lengths[prev];
            prev -= lengths[prev];
          }
          else
          {
            break;
          }
        }

        if (matched)
        {
          length += valid_length;
        }

        lengths[i] = length;
        longest = std::max(longest, length);
      }

      return longest;
    }
};

int main(void)
{
  Solution s;
  std::string a;

  while (std::cin >> a)
  {
    std::cout << s.longestValidParentheses(a) << '\n';
  }
  return 0;
}
