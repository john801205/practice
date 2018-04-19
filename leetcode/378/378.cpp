#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int kthSmallest(const std::vector<std::vector<int>> &matrix, int k)
    {
      int left = matrix.front().front(), right = matrix.back().back();

      while (left < right)
      {
        int middle = left + (right - left) / 2;

        int smaller = 0, equal = 0;
        for (const auto &row: matrix)
        {
          smaller += std::lower_bound(std::begin(row), std::end(row), middle) - std::begin(row);
          equal += std::upper_bound(std::begin(row), std::end(row), middle) - std::begin(row);
        }

        if (k > smaller && k <= equal)
          return middle;
        else if (k <= smaller)
          right = middle-1;
        else
          left = middle+1;
      }

      return left;
    }
};

int main()
{
  Solution s;
  assert(s.kthSmallest({{1,2},{1,3}}, 4) == 3);
  assert(s.kthSmallest({{1,5,9},{10,11,13},{12,13,15}}, 8) == 13);
  assert(s.kthSmallest({{1,5,9},{10,11,14},{12,13,15}}, 8) == 14);
  assert(s.kthSmallest({{1,5,9},{10,11,12},{12,13,15}}, 8) == 13);
  return 0;
}
