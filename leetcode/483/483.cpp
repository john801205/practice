#include <cassert>
#include <iostream>
#include <string>

class Solution
{
  public:
    std::string smallestGoodBase(const std::string n)
    {
      unsigned long long number = std::stoll(n);
      unsigned long long size = 0, temp = number;
      unsigned long long base = 1;

      while (temp != 0)
      {
        size++;
        temp /= 2;
      }

      for (; size >= 2; size--)
      {
        unsigned long long left = 2, right = number >> (size - 2);
        unsigned long long middle, sum = 0;

        while (left <= right)
        {
          bool overflow = false;
          middle = left + (right - left) / 2;
          sum = 0;

          for (unsigned long long i = 0, x = 1; sum <= number && i < size; i++)
          {
            if (sum > sum+x)
              overflow = true;

            sum += x;

            if (i+1 != size && x*middle/middle != x)
              overflow = true;
            else
              x *= middle;
          }

          if (overflow || sum > number)
            right = middle-1;
          else if (sum < number)
            left = middle+1;
          else
            break;
        }

        if (sum == number)
        {
          base = middle;
          break;
        }
      }

      return std::to_string(base);
    }
};

int main()
{
  Solution s;
  assert(s.smallestGoodBase("4681") == "8");
  assert(s.smallestGoodBase("13") == "3");
  assert(s.smallestGoodBase("1000000000000000000") == "999999999999999999");
  assert(s.smallestGoodBase("2") == "1");
  assert(s.smallestGoodBase("3") == "2");
  assert(s.smallestGoodBase("2251799813685247") == "2");
  assert(s.smallestGoodBase("919818571896748567") == "986");
  return 0;
}
