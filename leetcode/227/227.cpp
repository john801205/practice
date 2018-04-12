#include <cassert>
#include <cctype>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

class Solution
{
  public:
    int calculate(const std::string s)
    {
      std::unordered_map<char, int> pred ({{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}});
      std::stack<char> operators;
      std::stack<int> numbers;

      int number = 0;

      for (std::string::size_type i = 0; i < s.size(); i++)
      {
        if (s[i] == ' ')
        {
          continue;
        }
        else if (std::isdigit(s[i]))
        {
          number = number * 10 + s[i] - '0';
        }
        else
        {
          numbers.emplace(number);
          number = 0;

          while (!operators.empty() && pred[operators.top()] >= pred[s[i]])
          {
            int op2 = numbers.top();
            numbers.pop();
            int op1 = numbers.top();
            numbers.pop();
            char op = operators.top();
            operators.pop();

            if (op == '+')
              numbers.emplace(op1 + op2);
            else if (op == '-')
              numbers.emplace(op1 - op2);
            else if (op == '*')
              numbers.emplace(op1 * op2);
            else if (op == '/')
              numbers.emplace(op1 / op2);
          }

          operators.emplace(s[i]);
        }
      }

      numbers.emplace(number);

      while (!operators.empty())
      {
        int op2 = numbers.top();
        numbers.pop();
        int op1 = numbers.top();
        numbers.pop();
        char op = operators.top();
        operators.pop();

        if (op == '+')
          numbers.emplace(op1 + op2);
        else if (op == '-')
          numbers.emplace(op1 - op2);
        else if (op == '*')
          numbers.emplace(op1 * op2);
        else if (op == '/')
          numbers.emplace(op1 / op2);
      }

      return numbers.top();
    }
};

int main(void)
{
  Solution s;
  assert(s.calculate("3+2*2") == 7);
  assert(s.calculate(" 3 / 2  ") == 1);
  assert(s.calculate(" 3+5 / 2  ") == 5);
  return 0;
}
