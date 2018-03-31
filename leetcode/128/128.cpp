#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

class Solution
{
  public:
    int longestConsecutive(const std::vector<int> &nums)
    {
      std::unordered_map<int, std::vector<int>::size_type> maps;
      std::vector<int>::size_type longest = 0;

      for (const auto &num: nums)
      {
        if (maps.find(num) == maps.end())
        {
          std::vector<int>::size_type left  = (maps.find(num-1) != maps.end() ? maps[num-1]: 0);
          std::vector<int>::size_type right = (maps.find(num+1) != maps.end() ? maps[num+1]: 0);
          std::vector<int>::size_type sum   = left + right + 1;

          longest = std::max(longest, sum);

          maps[num] = sum;
          maps[num-left] = sum;
          maps[num+right] = sum;
        }
      }

      return longest;
    }
};

int main(void)
{
  Solution s;
  assert(s.longestConsecutive({100, 4, 200, 1, 3, 2}) == 4);
  assert(s.longestConsecutive({100,4,200,1,3,2, 3, 101, 102, 5, 99, 98}) == 5);
  assert(s.longestConsecutive({}) == 0);
  assert(s.longestConsecutive({1}) == 1);
  assert(s.longestConsecutive({1, 3, 5}) == 1);
  return 0;
}
