#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int minPatches(const std::vector<int> &nums, int n)
    {
      int patch = 0;
      long miss = 1;
      std::vector<int>::size_type i = 0;

      while (miss <= n)
      {
        if (i < nums.size() && nums[i] <= miss)
        {
          miss += nums[i];
          i++;
        }
        else
        {
          miss += miss;
          patch++;
        }
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
