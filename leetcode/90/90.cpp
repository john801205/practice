#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
  public:
    std::vector<std::vector<int>> subsetsWithDup(const std::vector<int> &nums)
    {
      std::vector<int> stack;
      std::vector<std::vector<int>> result;

      std::vector<int> sorted (nums);
      std::sort(std::begin(sorted), std::end(sorted));

      dfs(sorted, stack, 0, result);

      return result;
    }

  private:
    void dfs(const std::vector<int>              &nums,
                   std::vector<int>              &stack,
             const std::vector<int>::size_type    index,
                   std::vector<std::vector<int>> &result)
    {
      result.emplace_back(stack);

      for (std::vector<int>::size_type i = index; i < nums.size(); i++)
      {
        if (i == index || nums[i] != nums[i-1])
        {
          stack.emplace_back(nums[i]);
          dfs(nums, stack, i+1, result);
          stack.pop_back();
        }
      }
    }
};

int main()
{
  Solution s;
  s.subsetsWithDup({1,2,2,3,2});
  return 0;
}
