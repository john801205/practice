#include <cassert>
#include <climits>
#include <array>
#include <iostream>
#include <string>
#include <vector>

int mod(int a, int b)
{
  return (b + a % b) % b;
}

class Solution
{
  public:
    int findRotateSteps(const std::string ring, const std::string key)
    {
      std::array<std::vector<int>, 26> indexes;

      for (std::string::size_type i = 0; i < ring.size(); i++)
        indexes[ring[i] - 'a'].emplace_back(i);

      std::vector<std::pair<int, int>> prev = {{0, 0}};

      for (const auto &c: key)
      {
        std::vector<std::pair<int,int>> cur;

        for (const auto &index: indexes[c-'a'])
        {
          int min = INT_MAX;

          for (const auto &pair: prev)
          {
            int v1 = mod(pair.first - index, ring.size());
            int v2 = mod(index - pair.first, ring.size());

            min = std::min(min, std::min(v1, v2) + pair.second);
          }

          cur.emplace_back(index, min+1);
        }

        prev = cur;
      }

      int min = INT_MAX;

      for (const auto &pair: prev)
        min = std::min(min, pair.second);

      return min;
    }
};

int main()
{
  Solution s;
  assert(s.findRotateSteps("godding", "gd") == 4);
  assert(s.findRotateSteps("godding", "gdodg") == 11);
  assert(s.findRotateSteps("goddingodg", "gdodg") == 10);
  return 0;
}
