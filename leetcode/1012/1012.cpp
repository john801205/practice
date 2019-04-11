#include <cassert>
#include <string>
#include <vector>

class Solution
{
  public:
    int numDupDigitsAtMostN(const int N)
    {
      // Suppose number is ABCDE
      std::string digits(std::to_string(N+1));

      // calculate 0XXXX
      int noduplicates = 0;
      for (std::string::size_type i = 1, count = 9; i < digits.size(); i++)
      {
        noduplicates += count;
        count *= (10 - i);
      }

      std::vector<bool> used(10, false);
      for (std::string::size_type i = 0; i < digits.size(); i++)
      {
        // calculate A0XXX, A1XXX, A2XXX, ...
        int count = digits[i] - '0';

        // remove used digits
        int temp = 0;
        for (int j = 0; j < count; j++)
          if (used[j])
            temp++;
        count -= temp;

        // because we have calculate 0XXXX
        if (i == 0)
          count -= 1;

        int candidate = 9 - i;
        for (std::string::size_type j = i+1; j < digits.size(); j++)
        {
          count *= candidate;

          if (candidate > 0)
            candidate -= 1;
        }
        noduplicates += count;

        // mark the digit as being used
        if (used[digits[i] - '0'])
          break;
        used[digits[i] - '0'] = true;
      }

      return N - noduplicates;
    }
};

int main()
{
  Solution s;
  assert(s.numDupDigitsAtMostN(123) == 23);
  assert(s.numDupDigitsAtMostN(1230) == 428);
  assert(s.numDupDigitsAtMostN(1232) == 430);
  assert(s.numDupDigitsAtMostN(12321) == 6663);
  assert(s.numDupDigitsAtMostN(123212321) == 120820391);
  assert(s.numDupDigitsAtMostN(20) == 1);
  assert(s.numDupDigitsAtMostN(100) == 10);
  assert(s.numDupDigitsAtMostN(1000) == 262);
  assert(s.numDupDigitsAtMostN(123456789) == 121064705);
  assert(s.numDupDigitsAtMostN(987654321) == 982042551);
  return 0;
}
