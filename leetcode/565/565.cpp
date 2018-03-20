#include <iostream>
#include <vector>

class Solution
{
  public:
    int arrayNesting(std::vector<int>& nums)
    {
      int longest = 0;

      for (std::vector<int>::size_type i = 0; i < nums.size(); i++)
      {
        int length = 0;

        for (int j = i, k; nums[j] != -1; )
        {
          length++;

          k = nums[j];
          nums[j] = -1;
          j = k;
        }

        longest = std::max(longest, length);
      }

      return longest;
    }
};

int main(void)
{
  std::vector<int> nums = {5, 4, 0, 3, 1, 6, 2};

  Solution s;
  std::cerr << s.arrayNesting(nums) << '\n';

  return 0;
}
