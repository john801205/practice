#include <cassert>
#include <algorithm>
#include <iostream>
#include <stack>
#include <string>

class Solution
{
  public:
    std::string removeKdigits(const std::string num, int k)
    {
      std::string result;

      for (const auto &digit: num)
      {
        while (k > 0 && result.size() > 0 && result.back() > digit)
        {
          result.pop_back();
          k--;
        }

        result += digit;
      }

      result.resize(result.size() - k);

      for (std::string::size_type i = 0; i < result.size(); i++)
        if (result[i] != '0')
          return result.substr(i);

      return "0";
    }
};

int main()
{
  Solution s;
  assert(s.removeKdigits("1432219", 3) == "1219");
  assert(s.removeKdigits("10200", 1) == "200");
  assert(s.removeKdigits("10", 2) == "0");
  assert(s.removeKdigits("123456789", 3) == "123456");
  return 0;
}
