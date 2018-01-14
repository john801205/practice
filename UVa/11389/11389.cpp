#include <iostream>
#include <queue>

int main(void)
{
  int n, d, r;

  while (std::cin >> n >> d >> r)
  {
    if (n == 0 and d == 0 and r == 0)
      break;

    // drivers is a priority queue, which stores the remaining
    // allowed routes after assigning a morning bus routes
    std::priority_queue<int> drivers;
    for (int i = 0; i < n; i++)
    {
      int route;
      std::cin >> route;
      drivers.push(d - route);
    }

    // routes is a priority queue, which stores the afternoon
    // bus routes
    std::priority_queue<int> routes;
    for (int i = 0; i < n; i++)
    {
      int route;
      std::cin >> route;
      routes.push(route);
    }

    int overtime = 0;
    for (int i = 0; i < n; i++)
    {
      if (routes.top() > drivers.top())
        overtime += routes.top() - drivers.top();

      routes.pop();
      drivers.pop();
    }

    // the money is overtime times rate
    std::cout << overtime * r << '\n';
  }

  return 0;
}
