#include <cassert>
#include <map>
#include <vector>

class Solution
{
  public:
    int oddEvenJumps(const std::vector<int>& A)
    {
      std::map<int, int> maps;
      std::vector<bool> higher(A.size(), false);
      std::vector<bool> lower(A.size(), false);
      int count = 1;

      higher[A.size()-1] = true;
      lower[A.size()-1] = true;
      maps[A[A.size()-1]] = A.size()-1;

      for (int i = A.size()-2; i >= 0; i--)
      {
        auto itr = maps.upper_bound(A[i]);
        if (itr != maps.begin())
          lower[i] = higher[std::prev(itr)->second];

        itr = maps.lower_bound(A[i]);
        if (itr != maps.end())
          higher[i] = lower[itr->second];

        maps[A[i]] = i;
        if (higher[i])
          count += 1;
      }

      return count;
    }
};

int main()
{
  Solution s;
  assert(s.oddEvenJumps({10,13,12,14,15}) == 2);
  return 0;
}
