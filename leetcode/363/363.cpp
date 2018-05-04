#include <cassert>
#include <climits>
#include <iostream>
#include <set>
#include <vector>

class Solution
{
  public:
    int maxSumSubmatrix(const std::vector<std::vector<int>> &matrix,
                        const int k)
    {
      if (matrix.size() == 0)
        return 0;

      const std::vector<int>::size_type m = matrix.size();
      const std::vector<int>::size_type n = matrix[0].size();

      if (n > m)
        return maxSumSubmatrix(transpose(matrix), k);

      long long maxsum = LLONG_MIN;

      for (std::vector<int>::size_type left = 0; left < n; left++)
      {
        std::vector<int> cols (m, 0);

        for (std::vector<int>::size_type right = left; right < n; right++)
        {
          for (std::vector<int>::size_type i = 0; i < m; i++)
            cols[i] += matrix[i][right];

          std::multiset<long long> sets = {0};
          long long currentsum = 0;

          for (std::vector<int>::size_type i = 0; i < m; i++)
          {
            currentsum += cols[i];

            const auto itr = sets.lower_bound(currentsum - k);

            if (itr != sets.end())
              maxsum = std::max(maxsum, currentsum - (*itr));

            sets.emplace(currentsum);
          }
        }
      }

      return maxsum;
    }

    std::vector<std::vector<int>> transpose(const std::vector<std::vector<int>> &matrix)
    {
      const std::vector<int>::size_type m = matrix.size();
      const std::vector<int>::size_type n = matrix[0].size();

      std::vector<std::vector<int>> result (n, std::vector<int> (m));

      for (std::vector<int>::size_type i = 0; i < m; i++)
        for (std::vector<int>::size_type j = 0; j < n; j++)
          result[j][i] = matrix[i][j];

      return result;
    }
};

int main()
{
  Solution s;
  assert(s.maxSumSubmatrix({{1,0,1},{0,-2,3}}, 2) == 2);
  assert(s.maxSumSubmatrix({{2,2,-1}}, 0) == -1);
  assert(s.maxSumSubmatrix({{2,2,-1}}, 3) == 3);
  return 0;
}
