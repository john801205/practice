#include <iostream>
#include <unordered_set>
#include <vector>

class Solution
{
  public:
    std::vector<int> powerfulIntegers(int x, int y, int bound)
    {
      std::vector<int> ans;
      std::unordered_set<int> set;

      for (int xi = 1; xi <= bound - 1; xi *= x)
      {
        for (int yi = 1; yi <= bound - xi; yi *= y)
        {
          int num = xi+yi;
          if (set.find(num) != set.end())
            continue;

          set.insert(num);
          ans.emplace_back(num);

          if (y == 1 || (bound - xi)/y < yi)
            break;
        }

        if (x == 1 || (bound - 1) / x < xi)
          break;
      }

      return ans;
    }
};

int main()
{
  Solution s;
  s.powerfulIntegers(2, 1, 10);
  return 0;
}
