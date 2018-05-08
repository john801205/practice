#include <cassert>
#include <climits>
#include <iostream>

class Solution
{
  public:
    int preimageSizeFZF(int K)
    {
      return binarySearch(K+1) - binarySearch(K);
    }

    long binarySearch(int K)
    {
      long left = 0, right = LONG_MAX;

      while (left <= right)
      {
        long middle = left + (right - left) / 2;
        long zeros = trailingZeros(middle);

        if (zeros < K)
          left = middle + 1;
        else
          right = middle - 1;
      }

      return left;
    }

    long trailingZeros(long num)
    {
      long zeros = 0;

      while (num != 0)
      {
        zeros += num / 5;
        num /= 5;
      }

      return zeros;
    }
};

int main()
{
  Solution s;
  assert(s.preimageSizeFZF(0) == 5);
  assert(s.preimageSizeFZF(5) == 0);
  assert(s.preimageSizeFZF(11) == 0);
  assert(s.preimageSizeFZF(12) == 5);
  assert(s.preimageSizeFZF(999999996) == 0);
  assert(s.preimageSizeFZF(999999997) == 5);
  assert(s.preimageSizeFZF(999999998) == 5);
  assert(s.preimageSizeFZF(999999999) == 5);
  assert(s.preimageSizeFZF(1000000000) == 5);
  return 0;
}
