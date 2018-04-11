#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

struct Point
{
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

class Solution
{
  public:
    int maxPoints(std::vector<Point>& points)
    {
      if (points.size() <= 2)
        return points.size();

      int max = 0;

      for (std::vector<Point>::size_type i = 0; i < points.size(); i++)
      {
        std::unordered_map<int, std::unordered_map<int,int>> map;
        int duplicates = 0, vertical = 0, localmax = 0;

        for (std::vector<Point>::size_type j = 0; j < points.size(); j++)
        {
          if (points[i].x == points[j].x && points[i].y == points[j].y)
          {
            duplicates++;
          }
          else if (points[i].x == points[j].x)
          {
            vertical++;
          }
          else
          {
            int p = points[i].x - points[j].x;
            int q = points[i].y - points[j].y;
            int g = gcd(q, p);

            p /= g;
            q /= g;

            map[p][q]++;
            localmax = std::max(localmax, map[p][q]);
          }
        }

        localmax = std::max(localmax, vertical) + duplicates;
        max = std::max(max, localmax);
      }

      return max;
    }

    int gcd(int p, int q)
    {
      while (p % q != 0)
      {
        int temp = q;
        q = p % q;
        p = temp;
      }

      return q;
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
