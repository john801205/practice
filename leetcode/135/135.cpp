#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int candy(const std::vector<int>& ratings)
    {
      if (ratings.size() == 0)
      {
        return 0;
      }

      int count = 1;
      int current = 1;
      std::vector<int>::size_type decreasing = 0;
      std::vector<int>::size_type max_candy = 1;

      for (std::vector<int>::size_type i = 1; i < ratings.size(); i++)
      {
        if (ratings[i] > ratings[i-1])
        {
          current += 1;
          count += current;
          decreasing = 0;
          max_candy = current;
        }
        else if (ratings[i] == ratings[i-1])
        {
          current = 1;
          count += current;
          decreasing = 0;
          max_candy = current;
        }
        else
        {
          decreasing++;
          current = 1;
          count += (decreasing >= max_candy ? decreasing + 1: decreasing);
        }
      }

      return count;
    }
};

int main(void)
{
  Solution s;
  assert(s.candy({}) == 0);
  assert(s.candy({0}) == 1);
  assert(s.candy({0, 1, 2, 3, 4, 5}) == 21);
  assert(s.candy({0, -1, -2, -3, -4, -5}) == 21);
  assert(s.candy({0, -1, 1, -2, 1, -2, 3, -2, 3}) == 14);
  assert(s.candy({0, 0, 0, -1}) == 5);
  assert(s.candy({0, 0, 0, -1, -1, -2}) == 8);
  assert(s.candy({0, 1, 2, 3, -1, -2, -3, -4, -5}) == 27);
  assert(s.candy({0, 1, 2, 3, -1, -2, -3, -4, -5, -4, -3, -2, -1}) == 41);
  return 0;
}
