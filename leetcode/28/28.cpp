#include <cassert>

#include <iostream>
#include <string>
#include <vector>

class Solution
{
  public:
    int strStr(const std::string haystack, const std::string needle)
    {
      if (needle.size() == 0)
      {
        return 0;
      }

      std::vector<std::string::size_type> indexes = computeF(needle);

      for (std::string::size_type i = 0, j = 0; i < haystack.size();)
      {
        if (haystack[i] != needle[j])
        {
          if (j == 0)
          {
            i++;
          }
          else
          {
            j = indexes[j-1];
          }
        }
        else
        {
          i++;
          j++;
        }

        if (j == needle.size())
        {
          return i - j;
        }
      }

      return -1;
    }

    std::vector<std::string::size_type> computeF(const std::string string)
    {
      std::vector<std::string::size_type> result (string.size(), 0);

      for (std::string::size_type i = 1, j = 0; i < string.size();)
      {
        if (string[i] != string[j])
        {
          if (j == 0)
          {
            result[i] = 0;
            i++;
          }
          else
          {
            j = result[j-1];
          }
        }
        else
        {
          result[i] = j+1;
          i++;
          j++;
        }
      }

      return result;
    }
};

int main(void)
{
  Solution s;
  assert(s.strStr("shikisfatabababahahaha", "ababaabab") == -1);
  assert(s.strStr("hello", "ll") == 2);
  assert(s.strStr("aaaaa", "bba") == -1);
  assert(s.strStr("aaaabaaaaac", "aaaac") == 6);
  assert(s.strStr("", "") == 0);
  assert(s.strStr("aabc", "") == 0);
  assert(s.strStr("", "aabc") == -1);
  assert(s.strStr("mississippi", "issipi") == -1);
  assert(s.strStr("bbbbababbbaabbba", "abb") == 6);
  assert(s.strStr("aabaaabaaac", "aabaaac") == 4);

  return 0;
}
