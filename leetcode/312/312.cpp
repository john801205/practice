#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int maxCoins(const std::vector<int> &nums)
    {
      std::vector<int> numbers (nums);
      numbers.insert(numbers.begin(), 1);
      numbers.insert(numbers.end(), 1);

      std::vector<std::vector<int>> dp (numbers.size(), std::vector<int> (numbers.size(), 0));

      for (std::vector<int>::size_type len = 1; len+1 < numbers.size(); len++)
      {
        for (std::vector<int>::size_type left = 1; left+len < numbers.size(); left++)
        {
          std::vector<int>::size_type right = left+len-1;

          for (std::vector<int>::size_type i = left; i <= right; i++)
            dp[left][right] = std::max(dp[left][right],
                                       numbers[left-1]*numbers[i]*numbers[right+1]
                                       + dp[left][i-1] + dp[i+1][right]);
        }
      }

      return dp[1][nums.size()];
    }
};

int main(void)
{
  Solution s;
  std::cout << s.maxCoins({3,1,5,8}) << '\n';
  return 0;
}
