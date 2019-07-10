#include <string>
#include <vector>

class Solution
{
  public:
    std::vector<int> plusOne(const std::vector<int>& digits)
    {
      std::vector<int> result(digits);

      for (std::vector<int>::size_type i = 0, j = result.size()-1; i < j; i++, j--)
        std::swap(result[i], result[j]);

      int carry = 1;
      for (std::vector<int>::size_type i = 0; i < result.size() && carry != 0; i++)
      {
        result[i] += carry;
        carry = result[i] / 10;
        result[i] = result[i] % 10;
      }

      if (carry != 0)
        result.emplace_back(carry);

      for (std::vector<int>::size_type i = 0, j = result.size()-1; i < j; i++, j--)
        std::swap(result[i], result[j]);

      return result;
    }
};

int main()
{
  return 0;
}
