#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int nthUglyNumber(int n)
    {
      std::vector<int> numbers(n);
      std::vector<int>::size_type p1 = 0, p2 = 0, p3 = 0;

      numbers[0] = 1;
      for (int i = 1; i < n; i++)
      {
        numbers[i] = std::min(numbers[p1]*2, std::min(numbers[p2]*3, numbers[p3]*5));

        if (numbers[p1] * 2 == numbers[i])
          p1++;
        if (numbers[p2] * 3 == numbers[i])
          p2++;
        if (numbers[p3] * 5 == numbers[i])
          p3++;
      }

      return numbers.back();
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
