#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    std::vector<int> countBits(int num)
    {
      std::vector<int> result (num+1);

      result[0] = 0;
      for (int i = 1; i <= num; i++)
        result[i] = result[i - (i & -i)] + 1;

      return result;
    }
};

int main()
{
  Solution s;
  assert(s.countBits(5) == std::vector<int> ({0,1,1,2,1,2}));
  return 0;
}
