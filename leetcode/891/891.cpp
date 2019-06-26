#include <cassert>
#include <algorithm>
#include <vector>

#define MODULUS (1000*1000*1000 + 7)

class Solution
{
  public:
    int sumSubseqWidths(const std::vector<int> &A)
    {
      std::vector<int> nums(A);

      std::sort(nums.begin(), nums.end());

      long long result = 0, exp = 0, prev = 0;
      for (std::vector<int>::size_type i = 1; i < nums.size(); i++)
      {
        long long diff = nums[i] - nums[i-1];

        prev = (2LL * prev + diff * exp + diff) % MODULUS;
        exp = (2LL * exp + 2) % MODULUS;

        result = (result + prev) % MODULUS;
      }

      return result;
    }
};

int main()
{
  Solution s;
  assert(s.sumSubseqWidths({2,1,3}) == 6);
  assert(s.sumSubseqWidths({4,7,1,3}) == 44);
  return 0;
}
