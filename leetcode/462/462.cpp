#include <cassert>
#include <algorithm>
#include <vector>

class Solution
{
  public:
    int minMoves2(const std::vector<int> &nums)
    {
      std::vector<int> sorted_nums(nums);
      std::sort(sorted_nums.begin(), sorted_nums.end());

      int median = sorted_nums[sorted_nums.size() / 2];
      int move = 0;
      for (const auto &num: sorted_nums)
      {
        move += std::abs(num - median);
      }

      return move;
    }
};

int main()
{
  Solution s;
  assert(s.minMoves2({1, 2, 3}) == 2);
  assert(s.minMoves2({1, 2, 3, 9, 9, 9}) == 21);

  return 0;
}
