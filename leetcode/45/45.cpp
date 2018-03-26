#include <iostream>
#include <vector>

class Solution
{
  public:
    int jump(const std::vector<int> &nums)
    {
      std::vector<int>::size_type current_jump_max = 0;
      std::vector<int>::size_type last_jump_max    = 0;
      int                         jumps            = 0;

      for (std::vector<int>::size_type i = 0; i+1 < nums.size(); i++)
      {
        current_jump_max = std::max(current_jump_max, i + nums[i]);

        if (i == last_jump_max)
        {
          jumps++;
          last_jump_max = current_jump_max;
        }
      }

      return jumps;
    }
};

int main(void)
{
  std::vector<int> nums = {7,0,9,6,9,6,1,7,9,0,1,2,9,0,3};
  Solution s;
  std::cout << s.jump(nums) << '\n';
  return 0;
}
