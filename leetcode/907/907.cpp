#include <cassert>
#include <climits>

#include <iostream>
#include <stack>
#include <vector>

class Solution
{
  public:
    int sumSubarrayMins(const std::vector<int> &A)
    {
      std::vector<int> left(A.size()), right(A.size());

      std::stack<int> stack;
      for (int i = 0; i < A.size(); i++)
      {
        while (!stack.empty() && A[i] <= A[stack.top()])
          stack.pop();

        if (stack.empty())
          left[i] = -1;
        else
          left[i] = stack.top();

        stack.push(i);
      }

      while (!stack.empty()) stack.pop();
      for (int i = A.size()-1; i >= 0; i--)
      {
        while (!stack.empty() && A[i] < A[stack.top()])
          stack.pop();

        if (stack.empty())
          right[i] = A.size();
        else
          right[i] = stack.top();

        stack.push(i);
      }

      int ans = 0;
      for (int i = 0; i < A.size(); i++)
      {
        int count = (i - left[i]) * (right[i] - i);
        ans = (ans + count * A[i]) % 1000000007;
      }

      return ans;
    }
};

int main()
{
  Solution s;
  assert(s.sumSubarrayMins({4}) == 4);
  assert(s.sumSubarrayMins({3, 1, 2, 4}) == 17);
  assert(s.sumSubarrayMins({2, 2, 2, 2, 2}) == 30);
  assert(s.sumSubarrayMins({4, 1, 3, 30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000}) == 5130101);
  return 0;
}
