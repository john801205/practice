#include <climits>
#include <iostream>
#include <vector>

struct Interval
{
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

class Solution
{
  public:
    std::vector<Interval> insert(std::vector<Interval>& intervals,
                                 Interval newInterval)
    {
      std::vector<Interval> result;

      std::vector<Interval>::size_type i = 0;
      while (i < intervals.size() && intervals[i].end < newInterval.start)
      {
        result.push_back(intervals[i]);
        i++;
      }

      while (i < intervals.size() && intervals[i].start <= newInterval.end)
      {
        newInterval.start = std::min(intervals[i].start, newInterval.start);
        newInterval.end = std::max(intervals[i].end, newInterval.end);
        i++;
      }
      result.push_back(newInterval);

      while (i < intervals.size())
      {
        result.push_back(intervals[i]);
        i++;
      }

      return result;
    }
};

int main(void)
{
  return 0;
}
