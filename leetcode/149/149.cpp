#include <cassert>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Point
{
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

bool operator<(const Point &lhs, const Point &rhs)
{
  if (lhs.x != rhs.x)
  {
    return lhs.x < rhs.x;
  }
  else
  {
    return lhs.y < rhs.y;
  }
}

class Solution
{
  public:
    int maxPoints(std::vector<Point>& points)
    {
      if (points.size() == 0)
        return 0;

      std::unordered_map<int, std::unordered_map<int, int>> counts;
      for (const auto point: points)
        counts[point.x][point.y]++;

      std::vector<Point> uniques;
      std::sort(std::begin(points), std::end(points));

      for (std::vector<Point>::size_type i = 0; i < points.size(); i++)
        if (i == 0 || points[i].x != points[i-1].x || points[i].y != points[i-1].y)
          uniques.emplace_back(points[i].x, points[i].y);

      std::vector<std::unordered_map<double, int>> maps (uniques.size());
      int max = counts[points[0].x][points[0].y];

      for (std::vector<Point>::size_type i = 1; i < uniques.size(); i++)
      {
        std::unordered_set<double> sets;

        for (std::vector<Point>::size_type j = i; j-- > 0; )
        {
          double m = slope(uniques[j], uniques[i]);

          if (sets.find(m) != sets.end())
            continue;

          if (maps[j][m] == 0)
            maps[i][m] += counts[uniques[j].x][uniques[j].y] + counts[uniques[i].x][uniques[i].y];
          else
            maps[i][m] += maps[j][m] + counts[uniques[i].x][uniques[i].y];

          sets.emplace(m);

          max = std::max(max, maps[i][m]);
        }
      }

      return max;
    }

    double slope(Point a, Point b)
    {
      if (a.x == b.x)
      {
        return std::numeric_limits<double>::max();
      }
      else
      {
        return static_cast<double>(b.y - a.y) / (b.x - a.x);
      }
    }
};

int main(void)
{
  Solution s;

  std::vector<Point> points;
  points.clear();
  points.emplace_back(1,2);
  points.emplace_back(2,3);
  points.emplace_back(1,1);
  points.emplace_back(2,2);
  points.emplace_back(3,3);
  assert(s.maxPoints(points) == 3);

  points.clear();
  points.emplace_back(1,2);
  points.emplace_back(2,3);
  points.emplace_back(1,1);
  points.emplace_back(2,2);
  points.emplace_back(3,3);
  points.emplace_back(4,5);
  points.emplace_back(4,6);
  points.emplace_back(1,2);
  points.emplace_back(1,3);
  points.emplace_back(1,2);
  points.emplace_back(1,2);
  points.emplace_back(1,2);
  assert(s.maxPoints(points) == 7);


  points.clear();
  points.emplace_back(0,0);
  points.emplace_back(1,1);
  points.emplace_back(0,0);
  assert(s.maxPoints(points) == 3);

  points.clear();
  points.emplace_back(0,0);
  points.emplace_back(0,0);
  assert(s.maxPoints(points) == 2);
  return 0;
}
