#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int findMin(const std::vector<int>& nums)
    {
      std::vector<int>::size_type left = 0, right = nums.size()-1;

      while (left < right)
      {
        std::vector<int>::size_type middle = left + (right-left)/2;

        if (nums[middle] > nums[right])
        {
          left = middle+1;
        }
        else
        {
          right = middle;
        }
      }

      return nums[left];
    }
};

int main(void)
{
  Solution s;
  assert(s.findMin({0, 1, 2, 3, 4, 5, 6}) == 0);
  assert(s.findMin({1, 2, 3, 4, 5, 6, 0}) == 0);
  assert(s.findMin({2, 3, 4, 5, 6, 0, 1}) == 0);
  assert(s.findMin({3, 4, 5, 6, 0, 1, 2}) == 0);
  assert(s.findMin({0, 1, 2, 3, 4, 5, 6, 7}) == 0);
  assert(s.findMin({1, 2, 3, 4, 5, 6, 7, 0}) == 0);
  assert(s.findMin({2, 3, 4, 5, 6, 7, 0, 1}) == 0);
  assert(s.findMin({3, 4, 5, 6, 7, 0, 1, 2}) == 0);
  assert(s.findMin({4, 5, 6, 7, 0, 1, 2, 3}) == 0);
  assert(s.findMin({5, 6, 7, 0, 1, 2, 3, 4}) == 0);
  assert(s.findMin({6, 7, 0, 1, 2, 3, 4, 5}) == 0);
  return 0;
}
