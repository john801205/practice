#include <cassert>
#include <string>

#define MODULUS (1000*1000*1000+7)

class Solution
{
  public:
    int numDecodings(const std::string &s) {
      if (s.size() == 0)
        return 0;

      int prev = 1, prevprev = 0;
      for (std::string::size_type i = s.size(); i > 0; i--)
      {
        long long cur = prev;

        if (s[i-1] == '0')
          cur = 0;
        else if (i < s.size() && s[i-1] == '1')
        {
          if (s[i] >= '0' && s[i] <= '9')
            cur += prevprev;
          else if (s[i] == '*')
            cur += 9LL * prevprev;
        }
        else if (i < s.size() && s[i-1] == '2')
        {
          if (s[i] >= '0' && s[i] <= '6')
            cur += prevprev;
          else if (s[i] == '*')
            cur += 6LL * prevprev;
        }
        else if (s[i-1] == '*')
        {
          cur += 8LL * prev ;

          if (i < s.size() && s[i] >= '0' && s[i] <= '9')
            cur += prevprev;
          if (i < s.size() && s[i] >= '0' && s[i] <= '6')
            cur += prevprev;
          if (i < s.size() && s[i] == '*')
            cur += 15LL * prevprev;
        }

        prevprev = prev;
        prev = cur % MODULUS;
      }
      return prev;
    }
};

int main()
{
  Solution s;
  assert(s.numDecodings("*") == 9);
  assert(s.numDecodings("1*") == 18);
  assert(s.numDecodings("**") == 96);
  assert(s.numDecodings("***") == 999);
  assert(s.numDecodings("*1*") == 180);
  assert(s.numDecodings("*1***") == 18765);
  assert(s.numDecodings("*1***2***23***38*") == 744373011);
  assert(s.numDecodings("*1***2***23***38**********************") == 897713778);
  return 0;
}
