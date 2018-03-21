#include <iostream>
#include <vector>

class Solution
{
  public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums)
    {
      std::vector<bool>             selected(nums.size(), false);
      std::vector<int>              permutation;
      std::vector<std::vector<int>> result;

      dfs(nums, selected, permutation, result);

      return result;
    }

  private:
    void dfs(const std::vector<int>              &nums,
                   std::vector<bool>             &selected,
                   std::vector<int>              &permutation,
                   std::vector<std::vector<int>> &result)
    {
      bool non_selection = true;

      for (std::vector<bool>::size_type i = 0; i < selected.size(); i++)
      {
        if (!selected[i])
        {
          selected[i] = true;
          permutation.push_back(nums[i]);
          dfs(nums, selected, permutation, result);
          permutation.pop_back();
          selected[i] = false;
          non_selection = false;
        }
      }

      if (non_selection)
      {
        result.push_back(permutation);
      }
    }
};

int main(void)
{
  Solution s;
  std::vector<int> num = {1, 2, 3};
  auto r = s.permute(num);

  for (const auto &permutation: r)
  {
    for (const auto &n: permutation)
    {
      std::cerr << n << ' ';
    }
    std::cerr << '\n';
  }

  return 0;
}
