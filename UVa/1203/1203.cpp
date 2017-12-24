#include <iostream>
#include <queue>
#include <string>

class Query
{
  public:
    unsigned num, time, interval;

    Query(unsigned n, unsigned t): num(n), time(t), interval(t) {}
};

bool operator< (const Query& x, const Query& y)
{
  if (x.time != y.time)
    return x.time > y.time;
  else
    return x.num > y.num;
}

int main(void)
{
  std::priority_queue<Query> queries;
  std::string operation;

  while (std::cin >> operation) {
    if (operation == "#")
      break;

    unsigned num, interval;
    std::cin >> num >> interval;
    Query q(num, interval);
    queries.push(q);
  }

  unsigned K;
  std::cin >> K;

  for (unsigned i = 0; i < K; i++) {
    Query q = queries.top();
    queries.pop();

    std::cout << q.num << std::endl;
    q.time += q.interval;
    queries.push(q);
  }

  return 0;
}
