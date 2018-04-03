#include <cassert>
#include <array>
#include <iostream>
#include <limits>
#include <vector>

class Solution
{
  public:
    int maximumGap(const std::vector<int> &nums)
    {
      if (nums.size() < 2)
      {
        return 0;
      }

      std::vector<int> sorted = radixSort(nums);
      int gap = std::numeric_limits<int>::min();

      for (std::vector<int>::size_type i = 1; i < sorted.size(); i++)
      {
        gap = std::max(gap, sorted[i] - sorted[i-1]);
      }

      return gap;
    }

    std::vector<int> radixSort(const std::vector<int> &nums)
    {
      std::vector<int> sorted (nums);
      std::vector<int> temp (nums.size());

      for (int bit = 0; bit < 31; bit++)
      {
        std::array<std::vector<int>::size_type, 2> counts;

        for (auto &count: counts)
        {
          count = 0;
        }

        for (const auto &num: sorted)
        {
          counts[(num >> bit) & 1]++;
        }

        counts[1] += counts[0];

        for (std::vector<int>::size_type i = sorted.size(); i-- > 0; )
        {
          counts[(sorted[i] >> bit) & 1]--;
          temp[counts[(sorted[i] >> bit) & 1]] = sorted[i];
        }

        sorted = temp;
      }

      return sorted;
    }
};

int main(void)
{
  Solution s;
  assert(s.maximumGap({}) == 0);
  assert(s.maximumGap({1}) == 0);
  assert(s.maximumGap({1, 2}) == 1);
  assert(s.maximumGap({2, 1}) == 1);
  assert(s.maximumGap({2,1, 3, 0, 7, 4}) == 3);
  return 0;
}
