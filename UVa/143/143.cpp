#include <cmath>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

struct Point
{
  double x, y;

  Point (const double x, const double y): x(x), y(y) {}
};

double cross(const Point &a, const Point &b, const Point &c)
{
  return (a.x - b.x)*(a.y - c.y) - (a.y - b.y)*(a.x - c.x);
}

int main(void)
{
  double x1, y1, x2, y2, x3, y3;

  while (std::cin >> x1 >> y1
                  >> x2 >> y2
                  >> x3 >> y3)
  {
    if (x1 == 0 and y1 == 0
        and x2 == 0 and y2 == 0
        and x3 == 0 and y3 == 0)
      break;

    Point a(x1, y1),
          b(x2, y2),
          c(x3, y3);

    // calculate the bounding rectangle
    int left_x   = std::ceil(std::min({x1, x2, x3})),
        right_x  = std::floor(std::max({x1, x2, x3})),
        bottom_y = std::ceil(std::min({y1, y2, y3})),
        top_y    = std::floor(std::max({y1, y2, y3}));

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
        Point z(x, y);

        if (cross(a, b, z) * cross(a, c, z) > 1e-8)
          continue;

        if (cross(b, a, z) * cross(b, c, z) > 1e-8)
          continue;

        if (cross(c, a, z) * cross(c, b, z) > 1e-8)
          continue;

        inpoint++;
      }
    }

    std::cout << std::right << std::setw(4) << inpoint << '\n';
  }

  return 0;
}
