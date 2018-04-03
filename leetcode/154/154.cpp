#include <cassert>
#include <climits>
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
        std::vector<int>::size_type middle = left + (right-left) / 2;

        if (nums[middle] > nums[right])
        {
          left = middle+1;
        }
        else if (nums[middle] < nums[right])
        {
          right = middle;
        }
        else
        {
          right--;
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
  assert(s.findMin({0, 1, 1, 2, 2, 2, 2, 2, 2}) == 0);
  assert(s.findMin({2, 0, 1, 1, 2, 2, 2, 2, 2}) == 0);
  assert(s.findMin({2, 0, 1, 1, 2, 2, 2, 2, 2}) == 0);
  assert(s.findMin({2, 2, 0, 1, 2, 2, 2, 2, 2}) == 0);
  assert(s.findMin({2, 2, 2, 0, 2, 1, 2, 2, 2}) == 0);
  assert(s.findMin({2, 2, 2, 2, 0, 1, 1, 2, 2}) == 0);
  assert(s.findMin({2, 2, 2, 2, 2, 0, 1, 1, 2, 2}) == 0);
  assert(s.findMin({2, 2, 2, 2, 2, 2, 0, 1, 1, 2, 2}) == 0);
  assert(s.findMin({2, 2, 2, 2, 2, 2, 2, 0, 1, 1, 2, 2}) == 0);
  assert(s.findMin({2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 1, 2, 2}) == 0);
  assert(s.findMin({2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 1, 2, 2}) == 0);
  assert(s.findMin({2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 1, 2, 2}) == 0);
  return 0;
}
