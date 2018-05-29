#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
  public:
    std::vector<std::vector<int>> subsetsWithDup(const std::vector<int> &nums)
    {
      std::vector<std::vector<int>> result = {{}};

      std::vector<int> sorted (nums);
      std::sort(std::begin(sorted), std::end(sorted));

      std::vector<int>::size_type size = 0;
      for (std::vector<int>::size_type i = 0; i < sorted.size(); i++)
      {
        std::vector<int>::size_type begin = i > 0 && sorted[i] == sorted[i-1] ? size: 0;
        size = result.size();

        for (std::vector<int>::size_type j = begin; j < size; j++)
        {
          result.emplace_back(result[j]);
          result.back().emplace_back(sorted[i]);
        }
      }

      return result;
    }
};

int main()
{
  Solution s;
  s.subsetsWithDup({1,2,2,3,2});
  return 0;
}
