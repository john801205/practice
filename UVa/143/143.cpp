#include <cmath>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

struct Point
{
  double x, y;

  Point (const double x, const double y): x(x), y(y) {}

  friend bool operator<(const Point& a, const Point& b)
  {
    if (a.x != b.x)
      return a.x < b.x;
    else
      return a.y < b.y;
  }
};

struct Edge
{
  // y - y1 = m * (x - x1)
  const double m, x1, y1, x2, y2;
  const bool same;

  double slope(const Point& a, const Point& b)
  {
    if (a.x == b.x)
      return std::numeric_limits<double>::max();
    else
      return (a.y - b.y) / (a.x - b.x);
  }

  Edge (const Point& a, const Point& b): m{slope(a, b)},
                                         x1{a.x},
                                         y1{a.y},
                                         x2{b.x},
                                         y2{b.y},
                                         same{a.x == b.x and a.y == b.y}
  {
  }

  bool online(double x, double y) const
  {
    if (same)
      return x == this->x1 and y == this->y1;

    if (x1 > x2 and (x > x1 or x < x2))
      return false;

    if (x1 < x2 and (x < x1 or x > x2))
      return false;

    if (m == std::numeric_limits<double>::max())
      return x == this->x1;
    else
      return fabs(y - m * (x - this->x1) - this->y1) < 0.000001;
  }

  bool right(double x, double y) const
  {
    if (same)
      return false;

    if (m == std::numeric_limits<double>::max())
      return x > this->x1;
    else
      return y < m * (x - this->x1) + this->y1;
  }

  bool left(double x, double y) const
  {
    if (same)
      return false;

    if (m == std::numeric_limits<double>::max())
      return x < this->x1;
    else
      return y > m * (x - this->x1) + this->y1;
  }
};

int main(void)
{
  while (true)
  {
    unsigned zero = 0;
    std::vector<Point> triangle;

    int left_x   = std::numeric_limits<int>::max(),
        right_x  = std::numeric_limits<int>::min(),
        bottom_y = std::numeric_limits<int>::max(),
        top_y    = std::numeric_limits<int>::min();

    for (int i = 0; i < 3; i++)
    {
      double x, y;
      std::cin >> x >> y;
      triangle.emplace_back(x, y);

      if (x == 0 and y == 0)
        zero++;

      if (std::ceil(x) < left_x)
        left_x = std::ceil(x);
      if (std::floor(x) > right_x)
        right_x = std::floor(x);
      if (std::ceil(y) < bottom_y)
        bottom_y = std::ceil(y);
      if (std::floor(y) > top_y)
        top_y = std::floor(y);
    }

    if (zero == 3)
      break;

    std::sort(std::begin(triangle), std::end(triangle));
    // std::cerr << triangle[0].x << ' ' << triangle[1].y << '\n';

    std::vector<Edge> edges =
    {
      Edge(triangle[0], triangle[1]),
      Edge(triangle[1], triangle[2]),
      Edge(triangle[2], triangle[0]),
    };

    // std::cerr << edges[0].m << ' ' << edges[1].m << '\n';

    // Trees are only grown in [1, 99]
    if (left_x < 1)
      left_x = 1;
    if (right_x > 99)
      right_x = 99;
    if (bottom_y < 1)
      bottom_y = 1;
    if (top_y > 99)
      top_y = 99;

    unsigned inpoint = 0;
    for (int x = left_x; x <= right_x; x++)
    {
      for (int y = bottom_y; y <= top_y; y++)
      {
        if (edges[0].online(x, y)
            or edges[1].online(x, y)
            or edges[2].online(x, y))
        {
          inpoint++;
          // std::cerr << x << ' ' << y << '\n';
          // std::cerr << edges[0].same << ' ' << edges[1].same << ' ' << edges[2].same << '\n';
          // std::cerr << edges[0].online(99, 98) << ' ' << edges[1].online(99, 98) << ' ' << edges[2].online(99, 98) << '\n';
          continue;
        }

        if (edges[0].same or edges[1].same or edges[2].same)
          continue;

        if (edges[1].right(triangle[0].x, triangle[0].y))
        {
          // std::cerr << "right\n";
          unsigned right = 0;
          if (edges[0].right(x, y))
            right++;
          if (edges[1].right(x, y))
            right++;
          if (edges[2].right(x, y))
            right++;

          if (right == 2)
            inpoint++;
        }
        else
        {
          unsigned left = 0;
          if (edges[0].left(x, y))
            left++;
          if (edges[1].left(x, y))
            left++;
          if (edges[2].left(x, y))
            left++;

          if (left == 2)
            inpoint++;
        }
      }
    }

    std::cout << std::right << std::setw(4) << inpoint << '\n';
  }

  return 0;
}
