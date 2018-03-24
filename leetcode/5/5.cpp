#include <iostream>
#include <vector>
#include <string>

class Solution
{
  public:
    std::string longestPalindrome(const std::string &s)
    {
      std::string longest;

      for (std::string::size_type i = 0; i < s.size(); i++)
      {
        std::string::size_type left_length = 1, right_length = 1;

        while (i >= left_length
               && i + right_length < s.size()
               && s[i-left_length] == s[i+right_length])
        {
          left_length++;
          right_length++;
        }

        if (right_length+left_length-1 > longest.size())
        {
          longest = s.substr(i-left_length+1, right_length+left_length-1);
        }

        left_length = 1;
        right_length = 1;

        if (i < left_length || s[i-left_length] != s[i])
        {
          continue;
        }

        left_length++;
        while (i >= left_length
               && i + right_length < s.size()
               && s[i-left_length] == s[i+right_length])
        {
          left_length++;
          right_length++;
        }

        if (right_length+left_length-1 > longest.size())
        {
          longest = s.substr(i-left_length+1, right_length+left_length-1);
        }
      }

      return longest;
    }
};

int main(void)
{
  Solution s;
  std::string string("abcde");
  // std::string string("babbaba");
  std::cerr << string << '\n';
  std::cout << s.longestPalindrome(string) << '\n';

  return 0;
}
