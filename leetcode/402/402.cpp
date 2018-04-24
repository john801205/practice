#include <cassert>
#include <algorithm>
#include <iostream>
#include <stack>
#include <string>

class Solution
{
  public:
    std::string removeKdigits(const std::string num, const int k)
    {
      std::stack<char> stack;
      std::string::size_type i = 0;
      int count = 0;

      while (count < k)
      {
        while (stack.empty() || (i < num.size() && num[i] >= stack.top()))
        {
          stack.push(num[i]);
          i++;
        }

        stack.pop();
        count++;
      }

      std::string result;

      while (!stack.empty())
      {
        result += stack.top();
        stack.pop();
      }

      std::reverse(std::begin(result), std::end(result));
      result += num.substr(i);

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
  return 0;
}
