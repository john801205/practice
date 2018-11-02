#include <cmath>

#include <iostream>
#include <string>

class Pos
{
  public:
    Pos(const int x, const int y)
      : _x{x}, _y{y}
    {
    }

    void move(const char op)
    {
      if (op == 'U')
        _y += 1;
      else if (op == 'D')
        _y -= 1;
      else if (op == 'L')
        _x -= 1;
      else if (op == 'R')
        _x += 1;
    }

    void unmove(const char op)
    {
      if (op == 'U')
        _y -= 1;
      else if (op == 'D')
        _y += 1;
      else if (op == 'L')
        _x += 1;
      else if (op == 'R')
        _x -= 1;
    }

    bool isReachable(const Pos &target, const int steps)
    {
      int d = std::abs(target._x - _x) + std::abs(target._y - _y);

      return d <= steps && d%2 == steps%2;
    }

  private:
    int _x, _y;
};


// check checks whether we can go from (0, 0) to (x, y)
// through the sequence of operations and we can only change
// part of operations of size length
bool check(const std::string &operations,
           const int          number_of_operations,
           const int          x,
           const int          y,
           const int          length)
{
  Pos pos(0, 0);
  Pos target(x, y);

  for (int i = length; i < number_of_operations; i++)
  {
    pos.move(operations[i]);
  }

  for (int left = 0, right = length; right < number_of_operations; left++, right++)
  {
    if (pos.isReachable(target, length))
      return true;

    pos.move(operations[left]);
    pos.unmove(operations[right]);
  }

  return pos.isReachable(target, length);
}

int main(void)
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int         number_of_operations;
  std::string operations;
  int         x, y;

  std::cin >> number_of_operations;
  std::cin >> operations;
  std::cin >> x >> y;

  if (!Pos(0, 0).isReachable(Pos(x, y), number_of_operations))
  {
    std::cout << -1 << '\n';
    return 0;
  }

  int left = 0, right = number_of_operations;
  while (left < right)
  {
    int middle = (left + right) / 2;

    if (check(operations, number_of_operations, x, y, middle))
      right = middle;
    else
      left = middle+1;
  }

  std::cout << left << '\n';

  return 0;
}
