#include <cassert>
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

class Solution
{
  public:
    int scheduleCourse(const std::vector<std::vector<int>> &courses)
    {
      auto cmp = [] (const std::vector<int> &lhs, const std::vector<int> &rhs)
      {
        return lhs[1] != rhs[1] ? lhs[1] < rhs[1]: lhs[0] < rhs[0];
      };

      std::vector<std::vector<int>> copy (courses);
      std::priority_queue<int> queue;
      int time = 0;

      std::sort(std::begin(copy), std::end(copy), cmp);

      for (std::vector<int>::size_type i = 0; i < copy.size(); i++)
      {
        if (time + copy[i][0] <= copy[i][1])
        {
          time += copy[i][0];
          queue.push(copy[i][0]);
        }
        else if (!queue.empty() && copy[i][0] < queue.top())
        {
          time -= queue.top();
          time += copy[i][0];
          queue.pop();
          queue.push(copy[i][0]);
        }
      }

      return queue.size();
    }
};

int main()
{
  Solution s;
  assert(s.scheduleCourse({{100,200},{200,1300},{1000,1250},{2000,3200}}) == 3);
  assert(s.scheduleCourse({{100,2},{32,50}}) == 1);
  assert(s.scheduleCourse({{2,5},{2,19},{1,8},{1,3}}) == 4);
  assert(s.scheduleCourse({{5,15},{3,19},{6,7},{2,10},{5,16},{8,14},{10,11},{2,19}}) == 5);
  return 0;
}
