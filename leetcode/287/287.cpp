#include <iostream>
#include <vector>

class Solution
{
  public:
    int findDuplicate(const std::vector<int> &nums)
    {
      int left = 1, right = nums.size()-1;

      while (left < right)
      {
        int middle = left + (right - left) / 2;

        int smaller = 0, equal = 0;
        for (const auto &num: nums)
        {
          if (num < middle)
            smaller++;
          if (num <= middle)
            equal++;
        }

        if (equal - smaller > 1)
          return middle;
        else if (equal <= middle)
          left = middle+1;
        else
          right = middle;
      }

      return left;
    }
};

int main()
{
  return 0;
}
