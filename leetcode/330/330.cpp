#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int minPatches(const std::vector<int> &nums, int n)
    {
      int patch = 0;
      long minSuccess = 0;

      for (std::vector<int>::size_type i = 0; minSuccess < n && i < nums.size(); )
      {
        while (minSuccess < n && nums[i] > minSuccess+1)
        {
          patch++;
          minSuccess = 2 * minSuccess + 1;
        }

        minSuccess = minSuccess + nums[i];
        i++;
      }

      while (minSuccess < n)
      {
        patch++;
        minSuccess = 2 * minSuccess + 1;
      }

      return patch;
    }
};

int main()
{
  Solution s;
  assert(s.minPatches({1,3}, 6) == 1);
  assert(s.minPatches({1,5,10}, 20) == 2);
  assert(s.minPatches({1,2,2}, 5) == 0);
  assert(s.minPatches({1,3}, 31) == 4);
  assert(s.minPatches({1,3}, 1024) == 9);
  assert(s.minPatches({}, 1024) == 11);
  assert(s.minPatches({22222222}, 1024) == 11);
  assert(s.minPatches({1,2,31,33}, 2147483647) == 28);

  return 0;
}
