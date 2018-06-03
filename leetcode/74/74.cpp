#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    bool searchMatrix(const std::vector<std::vector<int>> &matrix, int target)
    {
      if (matrix.size() == 0 || matrix[0].size() == 0)
        return false;

      std::vector<int>::size_type m = matrix.size(), n = matrix[0].size();
      std::vector<int>::size_type low = 0, high = m*n-1;

      while (low < high)
      {
        std::vector<int>::size_type mid = low + (high - low) / 2;
        int num = matrix[mid/n][mid%n];

        if (num == target)
          return true;
        else if (num > target)
          high = mid - 1;
        else
          low = mid + 1;
      }

      return matrix[low/n][low%n] == target;
    }
};

int main()
{
  Solution s;
  assert(s.searchMatrix({{1,3,5,7},{10,11,16,20},{23,30,34,50}}, 3) == true);
  assert(s.searchMatrix({{1,3,5,7},{10,11,16,20},{23,30,34,50}}, 13) == false);
  assert(s.searchMatrix({{1}}, 0) == false);
  return 0;
}
