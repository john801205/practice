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
      std::vector<std::vector<int>::size_type> lasts (10, 0);

      while (num != 0)
      {
        digits.emplace_back(num % 10);
        num /= 10;
      }

      std::reverse(std::begin(digits), std::end(digits));

      for (std::vector<int>::size_type i = 0; i < digits.size(); i++)
        lasts[digits[i]] = i;

      for (std::vector<int>::size_type i = 0; i < digits.size(); i++)
      {
        for (std::vector<int>::size_type j = 9; j > i; j--)
        {
          if (lasts[j] > i)
          {
            std::swap(digits[lasts[j]], digits[i]);

            int result = 0;
            for (std::vector<int>::size_type k = 0; k < digits.size(); k++)
              result = result * 10 + digits[k];

            return result;
          }
        }
      }

      return num;
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
