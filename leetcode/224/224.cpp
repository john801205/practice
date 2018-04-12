#include <cassert>
#include <iostream>
#include <stack>
#include <string>

class Solution
{
  public:
    int calculate(const std::string s)
    {
      std::stack<int> operators;
      std::stack<int> numbers;

      int sign = 1;
      int number = 0;
      int result = 0;

      for (std::string::size_type i = 0; i < s.size(); i++)
      {
        if (s[i] == ' ')
        {
          continue;
        }
        else if (s[i] >= '0' && s[i] <= '9')
        {
          number = number * 10 + s[i] - '0';
        }
        else if (s[i] == '+')
        {
          result += number * sign;
          sign = 1;
          number = 0;
        }
        else if (s[i] == '-')
        {
          result += number * sign;
          sign = -1;
          number = 0;
        }
        else if (s[i] == '(')
        {
          operators.emplace(sign);
          numbers.emplace(result);

          sign = 1;
          number = 0;
          result = 0;
        }
        else if (s[i] == ')')
        {
          result += number * sign;
          result = numbers.top() + operators.top() * result;
          numbers.pop();
          operators.pop();

          sign = 1;
          number = 0;
        }
      }

      result += number * sign;
      return result;
    }
};

int main(void)
{
  Solution s;
  assert(s.calculate("1 + 1") == 2);
  assert(s.calculate(" 2-1 + 2 ") == 3);
  assert(s.calculate("(1+(4+5+2)-3)+(6+8)") == 23);
  assert(s.calculate("0-((1+2)+0)") == -3);
  return 0;
}
