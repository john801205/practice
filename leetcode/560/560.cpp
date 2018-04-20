#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

class Solution
{
  public:
    int subarraySum(const std::vector<int> &nums, const int k)
    {
      std::unordered_map<long long, int> maps = {{0, 1}};

      int count = 0;
      long long sum = 0;

      for (const auto &num: nums)
      {
        sum += num;

        if (maps.find(sum-k) != maps.end())
        {
          count += maps[sum-k];
        }

        maps[sum]++;
      }

      return count;
    }
};

int main()
{
  Solution s;
  assert(s.subarraySum({1,1,1}, 2) == 2);
  return 0;
}
