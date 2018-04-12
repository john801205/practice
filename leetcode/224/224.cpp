#include <cassert>
#include <iostream>
#include <stack>
#include <string>

class Solution
{
  public:
    int calculate(const std::string s)
    {
      std::stack<char> operators;
      std::stack<int> numbers;

      bool isNumber = false;
      int number = 0;
      for (std::string::size_type i = 0; i < s.size(); i++)
      {
        if (s[i] == ' ')
        {
          continue;
        }
        else if (s[i] >= '0' && s[i] <= '9')
        {
          isNumber = true;
          number = number * 10 + s[i] - '0';
        }
        else if (s[i] == '(')
        {
          operators.emplace('(');
          isNumber = false;
          number = 0;
        }
        else
        {
          if (isNumber)
          {
            numbers.emplace(number);
            isNumber = false;
            number = 0;
          }

          while (!operators.empty() && operators.top() != '(')
          {
            int op2 = numbers.top();
            numbers.pop();
            int op1 = numbers.top();
            numbers.pop();

            char op = operators.top();
            operators.pop();

            if (op == '+')
              numbers.emplace(op1+op2);
            else
              numbers.emplace(op1-op2);
          }

          if (s[i] == ')')
          {
            operators.pop();
            while (!operators.empty() && operators.top() != '(')
            {
              int op2 = numbers.top();
              numbers.pop();
              int op1 = numbers.top();
              numbers.pop();

              char op = operators.top();
              operators.pop();

              if (op == '+')
                numbers.emplace(op1+op2);
              else
                numbers.emplace(op1-op2);
            }
          }
          else
          {
            operators.emplace(s[i]);
          }
        }
      }

      if (isNumber)
      {
        numbers.emplace(number);
        isNumber = false;
        number = 0;

        while (!operators.empty() && operators.top() != '(')
        {
          int op2 = numbers.top();
          numbers.pop();
          int op1 = numbers.top();
          numbers.pop();

          char op = operators.top();
          operators.pop();

          if (op == '+')
            numbers.emplace(op1+op2);
          else
            numbers.emplace(op1-op2);
        }
      }

      return numbers.top();
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
