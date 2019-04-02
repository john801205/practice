#include <cassert>
#include <climits>
#include <iostream>
#include <map>
#include <vector>

class Solution
{
  public:
    bool containsNearbyAlmostDuplicate(const std::vector<int> &nums, int k, int t)
    {
      if (t < 0)
        return false;

      std::map<long, long> buckets;

      for (std::vector<int>::size_type i = 0; i < nums.size(); i++)
      {
        if (i > k)
        {
          long long num = (long long)nums[i-k-1] - INT_MIN;
          long long idx = num / ((long long)t + 1);
          buckets.erase(idx);
        }

        long long num = (long long)nums[i] - INT_MIN;
        long long idx = num / ((long long)t + 1);
        if (buckets.find(idx) != buckets.end())
          return true;

        if (buckets.find(idx+1) != buckets.end()
            && std::abs(buckets[idx+1] - num) <= t)
          return true;

        if (buckets.find(idx-1) != buckets.end()
            && std::abs(buckets[idx-1] - num) <= t)
          return true;

        buckets[idx] = num;
      }

      return false;
    }
};

int main()
{
  Solution s;
  assert(s.containsNearbyAlmostDuplicate({-1,1}, 1, -1) == false);
  assert(s.containsNearbyAlmostDuplicate({-1,2147483647}, 1, 2147483647) == false);
  assert(s.containsNearbyAlmostDuplicate({1,2,3,1,3,4,6,4,2,0,2,-2,4,5,6}, 1, 0) == false);
  assert(s.containsNearbyAlmostDuplicate({1,2,3,1}, 3, 0) == true);
  assert(s.containsNearbyAlmostDuplicate({1,0,1,1}, 1, 2) == true);
  assert(s.containsNearbyAlmostDuplicate({1,5,9,1,5,9}, 2, 3) == false);
  return 0;
}
