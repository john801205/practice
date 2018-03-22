#include <climits>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Solution
{
  public:
    int findMinDifference(std::vector<std::string>& timePoints)
    {
      std::vector<int> times (timePoints.size());
      int min_difference = INT_MAX;

      for (std::vector<int>::size_type i = 0; i < times.size(); i++)
      {
        times[i] = toInt(timePoints[i]);
      }

      std::sort(std::begin(times), std::end(times));

      for (std::vector<int>::size_type i = 0; i < times.size(); i++)
      {
        min_difference = std::min(min_difference, distance(times[i], times[(i+1) % times.size()]));
      }

      return min_difference;
    }

  private:
    int toInt(const std::string &time)
    {
      return (time[0] - '0') * 600
             + (time[1] - '0') * 60
             + (time[3] - '0') * 10
             + (time[4] - '0');
    }

    int distance(const int x, const int y)
    {
      int minus = std::abs(x - y);
      return std::min(minus, 1440 - minus);
    }
};

int main(void)
{
  return 0;
}
