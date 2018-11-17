#include <iostream>
#include <unordered_set>
#include <vector>

unsigned gcd(unsigned a, unsigned b)
{
  if (a < b)
    std::swap(a, b);

  while (a % b != 0)
  {
    unsigned temp = b;
    b = a % b;
    a = temp;
  }

  return b;
}

class Point
{
  public:
    long long _x, _y;

    Point(const long long x, const long long y)
      :_x{x}, _y{y}
    {
    }

    Point(const Point &p)
      :_x{p._x}, _y{p._y}
    {
    }

    bool operator==(const Point &p) const
    {
      return _x == p._x && _y == p._y;
    }
};

template<>
struct std::hash<Point>
{
  std::size_t operator()(const Point &p) const
  {
    return std::hash<long long>()(p._x) ^ std::hash<long long>()(p._y);
  }
};


class Line
{
  public:
    Line(const long long x1, const long long y1,
         const long long x2, const long long y2)
      :_p1{x1, y1}, _p2{x2, y2}, _A{}, _B{}, _C{}
    {
      _A = y2 - y1;
      _B = x1 - x2;
      _C = x1*y2 - x2*y1;
    }

    unsigned getIntegerCoordinates() const
    {
      if (_p1._x == _p2._x && _p1._y == _p2._y)
        return 1;
      else if (_p1._x == _p2._x)
        return std::abs(_p2._y - _p1._y) + 1;
      else if (_p1._y == _p2._y)
        return std::abs(_p2._x - _p1._x) + 1;
      else
        return gcd(std::abs(_p2._x - _p1._x),
                   std::abs(_p2._y - _p1._y)) + 1;
    }

    bool between(const Point &p) const
    {
      long long x1 = _p1._x, x2 = _p2._x;
      long long y1 = _p1._y, y2 = _p2._y;

      if (x1 > x2)
      {
        std::swap(x1, x2);
      }

      if (y1 > y2)
      {
        std::swap(y1, y2);
      }

      return p._x >= x1 && p._x <= x2
             && p._y >= y1 && p._y <= y2;
    }

    bool cross(const Line &l, Point &p) const
    {
      long long d = _A*l._B - _B*l._A;
      long long dx = _C*l._B - _B*l._C;
      long long dy = _C*l._A - _A*l._C;

      if (d == 0)
        return false;

      if (dx % d != 0 || dy % d != 0)
        return false;

      p._x = dx / d;
      p._y = -dy / d;

      return between(p) && l.between(p);
    }

  private:
    Point _p1, _p2;
    long long _A, _B, _C;
};

int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int                number_of_segments;
  unsigned long long number_of_integer_coordinates;
  std::vector<Line>  lines;

  std::cin >> number_of_segments;
  number_of_integer_coordinates = 0;

  for (int i = 0; i < number_of_segments; i++)
  {
    int Ax, Ay, Bx, By;
    std::cin >> Ax >> Ay >> Bx >> By;
    lines.emplace_back(Ax, Ay, Bx, By);

    std::unordered_set<Point> duplicates;
    Point                     dup(0,0);

    for (int j = 0; j < i; j++)
    {
      if (lines[i].cross(lines[j], dup))
      {
        duplicates.emplace(dup);
      }
    }

    number_of_integer_coordinates += lines[i].getIntegerCoordinates();
    number_of_integer_coordinates -= duplicates.size();
  }

  std::cout << number_of_integer_coordinates << '\n';

  return 0;
}
