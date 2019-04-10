#include <cassert>
#include <queue>
#include <vector>

class Solution
{
  public:
    int minRefuelStops(int target, int startFuel,
        const std::vector<std::vector<int>> &stations)
    {
      long long current = startFuel;
      int count = 0;
      std::vector<std::vector<int>>::size_type i = 0;
      std::priority_queue<int> pq;

      while (current < target)
      {
        while (i < stations.size() && stations[i][0] <= current)
        {
          pq.emplace(stations[i][1]);
          i++;
        }

        if (pq.empty())
          return -1;

        count++;
        current += pq.top();
        pq.pop();
      }

      return count;
    }
};

int main()
{
  Solution s;
  assert(s.minRefuelStops(1, 1, {}) == 0);
  assert(s.minRefuelStops(100, 1, {{10, 100}}) == -1);
  assert(s.minRefuelStops(100, 10, {{10, 60}, {20, 30}, {30, 30}, {60, 40}}) == 2);

  return 0;
}
