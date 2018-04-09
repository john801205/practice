#include <cassert>
#include <deque>
#include <iostream>
#include <vector>

class Solution
{
  public:
    std::vector<int> maxSlidingWindow(const std::vector<int>            &nums,
                                      const std::vector<int>::size_type  k)
    {
      std::deque<std::vector<int>::size_type> deque;
      std::vector<int> results;

      for (std::vector<int>::size_type i = 0; i < nums.size(); i++)
      {
        if (!deque.empty() && deque.front() + k == i)
        {
          deque.pop_front();
        }

        while (!deque.empty() && nums[i] >= nums[deque.back()])
        {
          deque.pop_back();
        }

        deque.push_back(i);

        if (i+1 >= k)
        {
          results.emplace_back(nums[deque.front()]);
        }
      }

      return results;
    }
};

int main(void)
{
  Solution s;
  assert(s.maxSlidingWindow({}, 0) == std::vector<int> ({}));
  assert(s.maxSlidingWindow({1,3,-1,-3,5,3,6,7}, 3) == std::vector<int> ({3,3,5,5,6,7}));
  assert(s.maxSlidingWindow({1,2,3,4,5,6}, 1) == std::vector<int> ({1,2,3,4,5,6}));
  assert(s.maxSlidingWindow({1,2,3,4,5,6}, 6) == std::vector<int> ({6}));
  return 0;
}
