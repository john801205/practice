#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>

class Solution
{
  public:
    bool isScramble(const std::string s1, const std::string s2)
    {
      static std::unordered_map<std::string, bool> caches;

      if (s1.size() != s2.size())
      {
        return false;
      }

      if (s1.size() == 1)
      {
        return s1 == s2;
      }

      if (caches.find(s1+s2) != caches.end())
      {
        return caches[s1+s2];
      }

      bool result = false;
      for (std::string::size_type len = 1; len < s1.size() && !result; len++)
      {
        if (isScramble(s1.substr(0, len), s2.substr(0, len))
            && isScramble(s1.substr(len), s2.substr(len)))
        {
          result = true;
        }
        else if (isScramble(s1.substr(0, len), s2.substr(s1.size()-len))
                 && isScramble(s1.substr(len), s2.substr(0, s1.size()-len)))
        {
          result = true;
        }
      }

      caches[s1+s2] = result;
      return result;
    }
};

int main(void)
{
  Solution s;
  assert(s.isScramble("rgeat", "great"));
  assert(s.isScramble("rgtae", "great"));
  assert(s.isScramble("a", "a"));
  assert(s.isScramble("abcd", "abcd"));
  assert(s.isScramble("abcd", "acbd"));
  assert(s.isScramble("abcd", "abdc"));
  assert(s.isScramble("abc", "aca") == false);
  return 0;
}
