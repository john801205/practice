#include <cassert>
#include <climits>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Solution
{
  public:
    std::vector<int> countSmaller(const std::vector<int> &nums)
    {
      std::vector<int>::size_type depth = std::ceil(std::log2(nums.size()));
      std::vector<int>::size_type size  = std::pow(2, depth+1) - 1;
      std::vector<int>::size_type shift = std::pow(2, depth) - 1;

      std::vector<int> segment_tree (size, 0);
      std::vector<int> sorted       (nums);
      std::unordered_map<int, std::vector<int>::size_type> maps;

      std::sort(std::begin(sorted), std::end(sorted));
      for (std::vector<int>::size_type i = 0; i < sorted.size(); i++)
      {
        maps[sorted[i]] = i;
      }

      std::vector<int> results (nums.size());

      for (std::vector<int>::size_type i = nums.size(); i-- > 0; )
      {
        std::vector<int>::size_type pos = maps[nums[i]];

        if (pos != 0)
        {
          results[i] = query(segment_tree, 0, 0, shift, 0, pos-1);
        }

        for (auto j = shift+pos; j != 0; j = (j-1)/2)
        {
          segment_tree[j]++;
        }
      }

      return results;
    }

    int query(const std::vector<int>            &segment_tree,
              const std::vector<int>::size_type  current,
              const std::vector<int>::size_type  current_left,
              const std::vector<int>::size_type  current_right,
              const std::vector<int>::size_type  target_left,
              const std::vector<int>::size_type  target_right)
    {
      if (current_left == target_left && current_right == target_right)
      {
        return segment_tree[current];
      }

      auto middle = current_left + (current_right - current_left)/2;
      if (target_right <= middle)
      {
        return query(segment_tree,
                     current*2+1, current_left, middle,
                     target_left, target_right);
      }
      else if (target_left > middle)
      {
        return query(segment_tree,
                     current*2+2, middle+1, current_right,
                     target_left, target_right);
      }
      else
      {
        return query(segment_tree,
                     current*2+1, current_left, middle,
                     target_left, middle)
             + query(segment_tree,
                     current*2+2, middle+1, current_right,
                     middle+1, target_right);
      }
    }
};

int main(void)
{
  Solution s;
  assert(s.countSmaller({}) == std::vector<int> ({}));
  assert(s.countSmaller({1}) == std::vector<int> ({0}));
  assert(s.countSmaller({5,2,6,1}) == std::vector<int> ({2, 1, 1, 0}));
  assert(s.countSmaller({5,2,6,12,3,7,1,5}) == std::vector<int> ({3,1,3,4,1,2,0,0}));
  assert(s.countSmaller({1,2,3,4,5,6,7}) == std::vector<int> ({0,0,0,0,0,0,0}));
  assert(s.countSmaller({7,6,5,4,3,2,1}) == std::vector<int> ({6,5,4,3,2,1,0}));
  assert(s.countSmaller({1,2,2,2,1,1}) == std::vector<int> ({0,2,2,2,0,0}));
  return 0;
}
