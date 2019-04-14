#include <cassert>
#include <cmath>

class Solution
{
  public:
    double myPow(double x, int n)
    {
      unsigned absn = std::abs((long)n);
      double pow = 1, xx = x;

      while (absn != 0)
      {
        if ((absn & 1) == 0x1)
          pow *= xx;

        absn >>= 1;
        xx *= xx;
      }

      return n < 0 ? 1/pow : pow;
    }
};

bool equal(double a, double b)
{
  return std::abs(a - b) < 1e-8;
}

int main()
{
  Solution s;
  assert(equal(s.myPow(1, -2147483648), 1.0));
  assert(equal(s.myPow(2, 0), 1.0));
  assert(equal(s.myPow(2, 10), 1024.0));
  assert(equal(s.myPow(2.1, 3), 9.261));
  assert(equal(s.myPow(2, -2), 0.25));
  return 0;
}
