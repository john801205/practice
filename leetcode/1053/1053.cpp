#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    std::vector<int> prevPermOpt1(const std::vector<int> &A)
    {
      if (isIncreasing(A))
        return A;

      std::vector<int>::size_type i, j;
      for (i = A.size()-1; i > 0; i--)
        if (A[i-1] > A[i])
          break;
      i--;

      for (j = i+1; j < A.size(); j++)
        if (A[j] >= A[i])
          break;
      j--;
      while (j > 0 && A[j] == A[j-1]) j--;

      auto B = A;
      std::swap(B[i], B[j]);

      return B;
    }

    bool isIncreasing(const std::vector<int> &A)
    {
      for (std::vector<int>::size_type i = 1; i < A.size(); i++)
        if (A[i-1] > A[i])
          return false;

      return true;
    }
};

int main()
{
  Solution s;
  assert(s.prevPermOpt1({3,2,1}) == std::vector<int>({3,1,2}));
  assert(s.prevPermOpt1({1,1,5}) == std::vector<int>({1,1,5}));
  assert(s.prevPermOpt1({1,9,4,6,7}) == std::vector<int>({1,7,4,6,9}));
  assert(s.prevPermOpt1({3,1,1,3}) == std::vector<int>({1,3,1,3}));
  assert(s.prevPermOpt1({1,9,4,6,7,10,10,1,9,11}) == std::vector<int>({1,9,4,6,7,10,9,1,10,11}));
  return 0;
}
