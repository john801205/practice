#include <algorithm>
#include <iostream>
#include <vector>

class Solution
{
  public:
    void wiggleSort(std::vector<int> &nums)
    {
      int n = nums.size();
      int mid = select(nums, 0, n-1, n/2+1);

#define A(i) nums[(1+(i)*2) % (n|1)]

      int l = 0, r = n-1, i = 0;

      while (i <= r)
      {
        if (A(i) > mid)
          std::swap(A(i++), A(l++));
        else if (A(i) < mid)
          std::swap(A(i), A(r--));
        else
          i++;
      }
    }

  private:
    int select(std::vector<int>            &nums,
               std::vector<int>::size_type  low,
               std::vector<int>::size_type  high,
               std::vector<int>::size_type  k)
    {
      std::vector<int>::size_type l = low+1, r = high, i = low+1;

      while (l <= r)
      {
        if (nums[i] >= nums[low])
          std::swap(nums[i], nums[r--]);
        else
          std::swap(nums[i++], nums[l++]);
      }

      std::swap(nums[low], nums[r]);

      if (r-low+1 == k)
        return nums[r];
      else if (r-low+1 > k)
        return select(nums, low, r-1, k);
      else
        return select(nums, r+1, high, k-(r-low+1));
    }
};

int main()
{
  std::vector<int> nums ({1,5,1,1,6,4});
  Solution s;
  s.wiggleSort(nums);
  for (const auto num: nums)
    std::cerr << num << ' ';
  std::cerr << '\n';
  return 0;
}
