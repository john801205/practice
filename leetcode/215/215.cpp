#include <iostream>
#include <random>
#include <vector>

std::random_device rd;
std::mt19937 rng(rd());

class Solution
{
  public:
    int findKthLargest(const std::vector<int> &nums, const int k)
    {
      if (nums.size() == 1)
        return nums[0];

      std::uniform_int_distribution<int> uni(1,nums.size());
      const int pivot = uni(rng)-1;

      std::vector<int> left, right;

      for (std::vector<int>::size_type i = 0; i < nums.size(); i++)
      {
        if (i == pivot)
          continue;

        if (nums[i] > nums[pivot])
          right.emplace_back(nums[i]);
        else
          left.emplace_back(nums[i]);
      }

      if (right.size() == k-1)
        return nums[pivot];
      else if (right.size() >= k)
        return findKthLargest(right, k);
      else
        return findKthLargest(left, k-right.size()-1);
    }
};

int main()
{
  Solution s;
  std::cout << s.findKthLargest({-1, -1}, 2) << '\n';
  return 0;
}
