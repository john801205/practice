#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

class Solution
{
  public:
    bool canIWin(int maxChoosableInteger, int desiredTotal)
    {
      if (maxChoosableInteger * (maxChoosableInteger + 1) / 2 < desiredTotal)
        return false;
      else if (maxChoosableInteger * (maxChoosableInteger + 1) / 2 == desiredTotal)
        return maxChoosableInteger % 2 != 0;

      std::unordered_map<int, std::unordered_map<std::string, bool>> cache;
      std::vector<bool> numbers (maxChoosableInteger, true);
      return dfs(numbers, desiredTotal, cache);
    }

    bool dfs(std::vector<bool> &numbers,
             int                desiredTotal,
             std::unordered_map<int, std::unordered_map<std::string, bool>> &cache)
    {
      std::string str;
      for (const auto &number: numbers)
        str += number ? '1': '0';

      if (cache.find(desiredTotal) != cache.end()
          && cache[desiredTotal].find(str) != cache[desiredTotal].end())
        return cache[desiredTotal][str];

      for (int i = numbers.size(); i-- > 0; )
      {
        if (numbers[i])
        {
          if (i+1 >= desiredTotal)
          {
            cache[desiredTotal][str] = true;
            return true;
          }

          numbers[i] = false;
          bool r = dfs(numbers, desiredTotal-i-1, cache);
          numbers[i] = true;

          if (!r)
          {
            cache[desiredTotal][str] = true;
            return true;
          }
        }
      }

      cache[desiredTotal][str] = false;
      return false;
    }
};

int main()
{
  Solution s;
  assert(s.canIWin(10, 100) == false);
  assert(s.canIWin(10, 11) == false);
  assert(s.canIWin(10, 3) == true);
  assert(s.canIWin(20, 100) == true);
  assert(s.canIWin(20, 210) == false);
  return 0;
}
