#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>

class Solution
{
  public:
    std::vector<std::vector<int>> combinationSum(const std::vector<int> &candidates,
                                                 const int               target)
    {
      std::vector<int>              numbers (candidates);
      std::vector<std::vector<int>> result;
      std::vector<int>              stack;

      std::sort(std::begin(numbers), std::end(numbers));
      dfs(numbers, target, 0, stack, result);

      return result;
    }

    void dfs(const std::vector<int>              &numbers,
             const int                            target,
             const std::vector<int>::size_type    begin,
                   std::vector<int>              &stack,
                   std::vector<std::vector<int>> &result)
    {
      if (target == 0)
      {
        result.emplace_back(stack);
        return;
      }

      for (std::vector<int>::size_type i = begin;
           i < numbers.size() && target >= numbers[i];
           ++i)
      {
        stack.emplace_back(numbers[i]);
        dfs(numbers, target-numbers[i], i, stack, result);
        stack.pop_back();
      }
    }
};

int main(void)
{
  Solution s;
  assert(s.combinationSum({2,3,6,7}, 7) == std::vector<std::vector<int>> ({{2, 2, 3}, {7}}));
  assert(s.combinationSum({1,2,3,4,5,6,7}, 7) == std::vector<std::vector<int>> ({{1,1,1,1,1,1,1},{1,1,1,1,1,2},{1,1,1,1,3},{1,1,1,2,2},{1,1,1,4},{1,1,2,3},{1,1,5},{1,2,2,2},{1,2,4},{1,3,3},{1,6},{2,2,3},{2,5},{3,4},{7}}));
  assert(s.combinationSum({1,2,3,4,5,6,7}, 0) == std::vector<std::vector<int>> ({{}}));
  assert(s.combinationSum({1,2,3,4,5,6,7}, 1) == std::vector<std::vector<int>> ({{1}}));
  return 0;
}
