#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int maximumSwap(int num)
    {
      std::vector<int> digits;

      while (num != 0)
      {
        digits.emplace_back(num % 10);
        num /= 10;
      }

      std::reverse(std::begin(digits), std::end(digits));

      for (std::vector<int>::size_type i = 0; i < digits.size(); i++)
      {
        std::vector<int>::size_type maxj = i;

        for (std::vector<int>::size_type j = i+1; j < digits.size(); j++)
        {
          if (digits[j] >= digits[maxj])
          {
            maxj = j;
          }
        }

        if (maxj != i && digits[maxj] != digits[i])
        {
          std::swap(digits[i], digits[maxj]);
          break;
        }
      }

      int result = 0;
      for (std::vector<int>::size_type i = 0; i < digits.size(); i++)
      {
        result = result * 10 + digits[i];
      }

      return result;
    }
};

int main()
{
  Solution s;
  assert(s.maximumSwap(2736) == 7236);
  assert(s.maximumSwap(27369) == 97362);
  assert(s.maximumSwap(9973) == 9973);
  assert(s.maximumSwap(1993) == 9913);
  return 0;
}
