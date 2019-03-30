#include <cassert>
#include <cmath>

#include <iostream>
#include <vector>

class Solution
{
  public:
    int minMoves(const std::vector<int>& nums)
    {
      if (nums.size() == 0)
        return 0;

      int move = 0;
      int prev_num = nums.front();
      int prev_count = 0;

      for (const auto &num: nums)
      {
        int num_moved = num + move;
        if (num_moved >= prev_num)
        {
          move += num_moved - prev_num;
          prev_num = num_moved;
        }
        else
        {
          move += (prev_num - num_moved) * prev_count;
          prev_num = num_moved + (prev_num - num_moved) * prev_count;
        }
        prev_count++;
      }

      return move;
    }
};

int main()
{
  Solution s;
  assert(s.minMoves({1, 2, 3}) == 3);
  assert(s.minMoves({83,86,77,15}) == 201);
  assert(s.minMoves({83,86,77,15,93,35,86,92,49,21}) == 487);
  return 0;
}
