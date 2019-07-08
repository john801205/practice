#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

class Solution {
  public:
    int subarraysWithKDistinct(const std::vector<int> &A, int K)
    {
      int left = -1, right = -1, result = 0, N = A.size();
      std::unordered_map<int, int> leftCounts, rightCounts;

      for (int i = 0; i < N; i++)
      {
        while (left+1 < N && leftCounts.size() < K)
        {
          left++;
          leftCounts[A[left]]++;
        }
        if (leftCounts.size() < K && left != N)
          left++;

        while (right+1 < N && rightCounts.size() <= K)
        {
          right++;
          rightCounts[A[right]]++;
        }
        if (rightCounts.size() <= K && right != N)
          right++;

        result += right - left;

        if (leftCounts[A[i]] == 1)
          leftCounts.erase(A[i]);
        else
          leftCounts[A[i]]--;

        if (rightCounts[A[i]] == 1)
          rightCounts.erase(A[i]);
        else
          rightCounts[A[i]]--;
      }

      return result;
    }
};

int main()
{
  Solution s;
  assert(s.subarraysWithKDistinct({1,2,1,2,3}, 2) == 7);
  assert(s.subarraysWithKDistinct({1,2,1,3,4}, 3) == 3);
  return 0;
}
