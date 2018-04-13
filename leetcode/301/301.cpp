#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

class Solution
{
  public:
    std::vector<std::string> removeInvalidParentheses(const std::string s)
    {
      std::vector<std::string> result;
      std::unordered_set<std::string> set;
      std::string::size_type left = 0, right = 0;

      for (std::string::size_type i = 0; i < s.size(); i++)
      {
        if (s[i] == '(')
          left++;
        else if (s[i] == ')')
          right++;

        right = std::min(left, right);
      }

      left = std::min(left, right);
      dfs(s, 0, '(', left, right, "", result, set);

      return result;
    }

    void dfs(const std::string                     &s,
                   std::string::size_type           pos,
             const char                             target,
                   std::string::size_type           left,
                   std::string::size_type           right,
                   std::string                      current,
                   std::vector<std::string>        &result,
                   std::unordered_set<std::string> &set)
    {
      // std::cerr << pos << ' ' << target << '\t' << left << ' ' << right << '\t' << current << '\n';
      if (pos == s.size())
      {
        if (left == 0 && right == 0 && set.find(current) == set.end())
        {
          result.emplace_back(current);
          set.emplace(current);
        }

        return;
      }

      while (pos < s.size() && s[pos] != target)
      {
        if (s[pos] != ')' && s[pos] != '(')
          current += s[pos];

        pos++;
      }

      std::string::size_type end = pos < s.size() ? pos+1: pos;
      while (end < s.size() && s[end] == target)
      {
        end++;
      }

      // std::cerr << pos << '\t' << end << '\n';
      dfs(s, end, ')' - target + '(', left, right, current, result, set);

      if (end < s.size() && s[end] != '(' && s[end] != ')')
      {
        if ((target == '(' && left != 0) || (target == ')' && right != 0))
        {
          dfs(s, end, target, left, right, current, result, set);
        }
      }

      for (std::string::size_type i = pos; i < end; i++)
      {
        if (target == ')' && right == left)
          break;
        else if (target == ')' && right == 0)
          break;
        else if (target == '(' && left == 0)
          break;

        current += target;

        if (target == '(')
          left--;
        else
          right--;

        dfs(s, end, ')' - target + '(', left, right, current, result, set);
        if (end < s.size() && s[end] != '(' && s[end] != ')')
        {
          if ((target == '(' && left != 0) || (target == ')' && right != 0))
          {
            dfs(s, end, target, left, right, current, result, set);
          }
        }
      }
    }
};

int main(void)
{
  Solution s;
  assert(s.removeInvalidParentheses("()())()") == std::vector<std::string> ({"(())()","()()()"}));
  assert(s.removeInvalidParentheses("(a)())()") == std::vector<std::string> ({"(a())()","(a)()()"}));
  assert(s.removeInvalidParentheses(")(") == std::vector<std::string> ({""}));
  assert(s.removeInvalidParentheses("()(())(a)())()(b))())") == std::vector<std::string> ({"((((a)())()(b))())","((()(a())()(b))())","((()(a)()()(b))())","((()(a)())((b))())","((()(a)())()(b)())","((()(a)())()(b))()","((())(a()()(b))())","((())(a())((b))())","((())(a())()(b)())","((())(a())()(b))()","((())(a)(()(b))())","((())(a)()((b))())","((())(a)()()(b)())","((())(a)()()(b))()","((())(a)())((b)())","((())(a)())((b))()","((())(a)())()(b())","((())(a)())()(b)()","()(((a())()(b))())","()(((a)()()(b))())","()(((a)())((b))())","()(((a)())()(b)())","()(((a)())()(b))()","()(()(a()()(b))())","()(()(a())((b))())","()(()(a())()(b)())","()(()(a())()(b))()","()(()(a)(()(b))())","()(()(a)()((b))())","()(()(a)()()(b)())","()(()(a)()()(b))()","()(()(a)())((b)())","()(()(a)())((b))()","()(()(a)())()(b())","()(()(a)())()(b)()","()(())(a(()(b))())","()(())(a()((b))())","()(())(a()()(b)())","()(())(a()()(b))()","()(())(a())((b)())","()(())(a())((b))()","()(())(a())()(b())","()(())(a())()(b)()","()(())(a)(((b))())","()(())(a)(()(b)())","()(())(a)(()(b))()","()(())(a)()((b)())","()(())(a)()((b))()","()(())(a)()()(b())","()(())(a)()()(b)()"}));
  assert(s.removeInvalidParentheses("n") == std::vector<std::string> ({"n"}));
  assert(s.removeInvalidParentheses(")(n") == std::vector<std::string> ({"n"}));
  assert(s.removeInvalidParentheses(")()(") == std::vector<std::string> ({"()"}));
  assert(s.removeInvalidParentheses("p(r)") == std::vector<std::string> ({"p(r)"}));
  assert(s.removeInvalidParentheses("(j))(") == std::vector<std::string> ({"(j)"}));
  assert(s.removeInvalidParentheses("(()y") == std::vector<std::string> ({"()y"}));
  assert(s.removeInvalidParentheses("())(()") == std::vector<std::string> ({"()()"}));
  assert(s.removeInvalidParentheses("())(((()m)(") == std::vector<std::string> ({"()(()m)"}));
  return 0;
}
