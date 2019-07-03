#include <cassert>
#include <string>

class Solution
{
  public:
    int numDecodings(const std::string &s) {
      if (s.size() == 0)
        return 0;

      int prev = 1, prevprev = 0;

      for (std::string::size_type i = s.size(); i > 0; i--) {
        int cur = prev;

        if (s[i-1] == '0')
          cur = 0;
        else if (i < s.size() && s[i-1] == '1')
          cur += prevprev;
        else if (i < s.size() && s[i-1] == '2' && s[i] <= '6')
          cur += prevprev;

        prevprev = prev;
        prev = cur;
      }

      return prev;
    }
};

int main()
{
  Solution s;
  assert(s.numDecodings("0") == 0);
  assert(s.numDecodings("10") == 1);
  assert(s.numDecodings("12") == 2);
  assert(s.numDecodings("226") == 3);
  return 0;
}
