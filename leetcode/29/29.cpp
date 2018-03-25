#include <climits>

#include <iostream>
#include <limits>

class Solution
{
  public:
    int divide(int dividend, int divisor)
    {
      if (divisor == 0 || (dividend == INT_MIN && divisor == -1))
      {
        return INT_MAX;
      }

      bool negative = ((dividend < 0) != (divisor < 0));
      unsigned dividend_ = std::abs(dividend), divisor_ = std::abs(divisor);

      // find the highest number such that divisor_ * (2 ^ x) <= UINT_MAX
      unsigned count = 0;
      unsigned largest_bit = 1 << (std::numeric_limits<unsigned>::digits - 1);
      while ((divisor_ & largest_bit) == 0 && divisor_ < dividend_)
      {
        divisor_ <<= 1;
        count++;
      }

      int result = 0;
      for (unsigned i = count; i > 0; i--)
      {
        if (dividend_ >= divisor_)
        {
          dividend_ -= divisor_;
          result |= 1;
        }

        result <<= 1;
        divisor_ >>= 1;
      }

      if (dividend_ >= divisor_)
      {
        dividend_ -= divisor_;
        result |= 1;
      }

      return (negative ? 0 - result : result);
    }

};

int main(void)
{
  Solution s;

  int a, b;

  while (std::cin >> a >> b)
  {
    std::cout << s.divide(a, b) << '\n';
  }

  return 0;
}
