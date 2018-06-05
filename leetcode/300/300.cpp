#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int lengthOfLIS(const std::vector<int> &nums)
    {
      std::vector<int> lengths;

      for (const auto &num: nums)
      {
        int left = 0, right = lengths.size()-1;

        while (left < right)
        {
          int mid = left + (right - left) / 2;

          if (lengths[mid] < num)
            left = mid+1;
          else
            right = mid;
        }

        if (left == lengths.size() || lengths[left] < num)
        {
          lengths.emplace_back(num);
        }
        else
        {
          lengths[left] = num;
        }
      }

      return lengths.size();
    }
};

int main()
{
  Solution s;
  assert(s.lengthOfLIS({10,9,2,5,3,7,101,18}) == 4);
  assert(s.lengthOfLIS({10,9,2,2,5,3,7,101,18}) == 4);
  assert(s.lengthOfLIS({-2,-1}) == 2);
  assert(s.lengthOfLIS({0}) == 1);
  assert(s.lengthOfLIS({4,10,4,3,8,9}) == 3);
  return 0;
}
