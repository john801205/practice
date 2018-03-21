#include <algorithm>
#include <iostream>
#include <vector>

class Solution
{
  public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums)
    {
      std::vector<std::vector<int>> result;
      dfs(nums, 0, result);
      return result;
    }

  private:
    void dfs(std::vector<int>              &nums,
             std::vector<int>::size_type    index,
             std::vector<std::vector<int>> &result)
    {
      if (index >= nums.size()-1)
      {
        result.push_back(nums);
        return;
      }


      for (std::vector<bool>::size_type i = index; i < nums.size(); i++)
      {
        std::swap(nums[index], nums[i]);
        dfs(nums, index+1, result);
        std::swap(nums[index], nums[i]);
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
