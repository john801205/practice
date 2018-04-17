#include <iostream>
#include <vector>

class Solution
{
  public:
    std::vector<int> singleNumber(const std::vector<int> &nums)
    {
      std::vector<int> results (2, 0);
      int val = 0;

      for (const auto &num: nums)
        val = val ^ num;

      val = val & -val;
      for (const auto &num: nums)
      {
        if (num & val)
          results[0] = results[0] ^ num;
        else
          results[1] = results[1] ^ num;
      }

      return results;
    }
};

int main(void)
{
  return 0;
}
