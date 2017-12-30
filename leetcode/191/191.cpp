#include <iostream>

class Solution {
  public:
    int hammingWeight(uint32_t n) {
      int number_of_one_bits = 0;

      while (n != 0) {
        number_of_one_bits++;
        n = n & (n-1);
      }

      return number_of_one_bits;
    }
};

int main(void)
{
  std::cout << Solution().hammingWeight(13) << '\n';
  return 0;
}
