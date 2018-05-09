#include <cassert>
#include <iostream>
#include <set>

class Solution
{
  public:
    int nthUglyNumber(int n)
    {
      std::set<long> sets = {1};

      for (int i = 1; i < n; i++)
      {
        long number = *sets.begin();
        sets.erase(sets.begin());

        sets.emplace(number * 2);
        sets.emplace(number * 3);
        sets.emplace(number * 5);
      }

      return *sets.begin();
    }
};

int main()
{
  Solution s;
  assert(s.nthUglyNumber(1) == 1);
  assert(s.nthUglyNumber(2) == 2);
  assert(s.nthUglyNumber(3) == 3);
  assert(s.nthUglyNumber(4) == 4);
  assert(s.nthUglyNumber(5) == 5);
  assert(s.nthUglyNumber(6) == 6);
  assert(s.nthUglyNumber(7) == 8);
  assert(s.nthUglyNumber(8) == 9);
  assert(s.nthUglyNumber(9) == 10);
  assert(s.nthUglyNumber(10) == 12);
  assert(s.nthUglyNumber(1690) == 2123366400);
  return 0;
}
