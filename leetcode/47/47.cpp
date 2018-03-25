#include <algorithm>
#include <iostream>
#include <vector>

class Solution
{
  public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums)
    {
      std::vector<std::vector<int>> result;

      std::sort(std::begin(nums), std::end(nums));
      dfs(nums, 0, result);

      return result;
    }

  private:
    void dfs(std::vector<int>               nums,
             std::vector<int>::size_type    index,
             std::vector<std::vector<int>> &result)
    {
      if (index >= nums.size() - 1)
      {
        result.emplace_back(nums);
        return;
      }

      for (std::vector<int>::size_type i = index; i < nums.size(); i++)
      {
        if (i == index || nums[i] != nums[index])
        {
          std::swap(nums[i], nums[index]);
          dfs(nums, index+1, result);
        }
      }
    }
};

int main(void)
{
  Solution s;
  std::vector<int> num = {1, 1, 3, 3};
  auto r = s.permuteUnique(num);

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
