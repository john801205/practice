#include <unordered_map>
#include <vector>

class Solution
{
  public:
    int numRabbits(const std::vector<int>& answers)
    {
      int result = 0;
      std::unordered_map<int, int> counts;

      for (const auto &num: answers)
      {
        auto &count = counts[num];
        if (count == 0)
          result += num + 1;

        if (count + 1 <= num)
          count++;
        else
          count = 0;
      }

      return result;
    }
};

int main()
{
  return 0;
}
