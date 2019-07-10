#include <algorithm>
#include <queue>
#include <vector>

struct Interval
{
  int L, R;

  Interval(int l, int r): L{l}, R{r} {}

  bool operator<(const Interval &x)
  {
    if (L != x.L)
      return L < x.L;
    return R < x.R;
  }
};

class Solution {
  public:
    int minMeetingRooms(const std::vector<std::vector<int>> &intervals)
    {
      if (intervals.size() == 0)
        return 0;

      std::vector<Interval> sorted;
      for (const auto &interval: intervals)
        sorted.emplace_back(interval[0], interval[1]);
      std::sort(sorted.begin(), sorted.end());

      std::priority_queue<int, std::vector<int>, std::greater<int>> rooms;

      for (const auto &meeting: sorted)
      {
        if (!rooms.empty() && meeting.L >= rooms.top())
          rooms.pop();

        rooms.push(meeting.R);
      }

      return rooms.size();
    }
};

int main()
{
  return 0;
}
