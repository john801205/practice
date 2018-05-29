#include <iostream>
#include <vector>

class Solution
{
  public:
    std::vector<std::vector<int>> subsets(const std::vector<int> &nums)
    {
      std::vector<std::vector<int>> result;
      std::vector<int> stack;
      dfs(nums, stack, 0, result);

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
        stack.emplace_back(nums[i]);
        dfs(nums, stack, i+1, result);
        stack.pop_back();
      }
    }
};

int main()
{
  return 0;
}
