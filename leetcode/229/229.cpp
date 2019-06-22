#include <cassert>
#include <iostream>
#include <vector>

class Solution
{
  public:
    std::vector<int> majorityElement(const std::vector<int> &nums)
    {
      int cand1 = 99999, cand2 = 999999;
      int count1 = 0, count2 = 0;

      for (const auto &num: nums)
      {
        if (count1 == 0 && num != cand2)
        {
          cand1 = num;
          count1 = 1;
          diff2++;
        }
        else if (count2 == 0 && num != cand1)
        {
          cand2 = num;
          count2 = 1;
          diff1++;
        }
        else if (num == cand1)
        {
          count1++;
          diff2++;
        }
        else if (num == cand2)
        {
          count2++;
          diff1++;
        }
        else
        {
          diff1++;
          diff2++;
        }

        while (diff1 >= 2 && count1 > 0)
        {
          count1--;
          diff1 -= 2;
        }
        while (diff2 >= 2 && count2 > 0)
        {
          count2--;
          diff2 -= 2;
        }

        if (count1 == 0)
        {
          std::swap(count1, count2);
          std::swap(cand1, cand2);
          std::swap(diff1, diff2);
        }
      }

      std::vector<int> result;
      if (count1 > 0)
      {
        unsigned int count = 0;
        for (const auto &num: nums)
          if (num == cand1)
            count++;

        if (count > nums.size() / 3)
          result.emplace_back(cand1);
      }
      if (count2 > 0)
      {
        unsigned int count = 0;
        for (const auto &num: nums)
          if (num == cand2)
            count++;

        if (count > nums.size() / 3)
          result.emplace_back(cand2);
      }

      return result;
    }
};

int main()
{
  Solution s;
  assert(s.majorityElement({1,2,3,4}) == std::vector<int>({}));
  assert(s.majorityElement({2,3,3,2}) == std::vector<int>({3,2}));
  assert(s.majorityElement({2,3,3}) == std::vector<int>({3}));
  assert(s.majorityElement({3,2,3}) == std::vector<int>({3}));
  assert(s.majorityElement({1,1,1,3,3,2,2,2}) == std::vector<int>({1,2}));
  assert(s.majorityElement({1,1,1,3,3,3,2,2,2}) == std::vector<int>({}));
  assert(s.majorityElement({1,1,3,3,3,2,2,2}) == std::vector<int>({3,2}));
  return 0;
}
