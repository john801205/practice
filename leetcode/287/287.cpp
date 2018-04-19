#include <iostream>
#include <vector>

class Solution
{
  public:
    int findDuplicate(const std::vector<int> &nums)
    {
      int tortoise = 0, hare = 0;

      do
      {
        tortoise = nums[tortoise];
        hare = nums[nums[hare]];
      }
      while (tortoise != hare);

      int ptr1 = nums[0], ptr2 = tortoise;

      while (ptr1 != ptr2)
      {
        ptr1 = nums[ptr1];
        ptr2 = nums[ptr2];
      }

      return ptr1;
    }
};

int main()
{
  return 0;
}
