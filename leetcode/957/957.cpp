#include <cassert>
#include <unordered_map>
#include <vector>

class Solution
{
  public:
    std::vector<int> prisonAfterNDays(const std::vector<int> cells, int N)
    {
      std::unordered_map<int, int> maps;
      std::vector<int> cur(cells), next(cells.size(), 0);

      while (N > 0)
      {
        N--;

        for (std::vector<int>::size_type i = 1; i+1 < next.size(); i++)
          next[i] = (cur[i-1] == cur[i+1] ? 1: 0);

        cur = next;
        const int number = toNumber(cur);
        if (maps.find(number) != maps.end())
          N %= maps[number] - N;
        else
          maps[number] = N;
      }

      return cur;
    }

    unsigned int toNumber(const std::vector<int> &cells)
    {
      int number = 0;
      for (std::vector<int>::size_type i = 0; i < cells.size(); i++)
        number = number * 2 + cells[i];
      return number;
    }
};

int main()
{
  Solution s;
  assert(s.prisonAfterNDays({0,1,0,1,1,0,0,1}, 1) == std::vector<int>({0, 1, 1, 0, 0, 0, 0, 0}));
  assert(s.prisonAfterNDays({0,1,0,1,1,0,0,1}, 7) == std::vector<int>({0, 0, 1, 1, 0, 0, 0, 0}));
  assert(s.prisonAfterNDays({1,0,0,1,0,0,1,0}, 1000000000) == std::vector<int>({0,0,1,1,1,1,1,0}));
  return 0;
}
