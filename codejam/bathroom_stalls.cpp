#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

std::pair<int, int> f(int N, int K)
{
  std::priority_queue<int> queue;
  std::unordered_map<int, int> map;
  int persons = 0;

  queue.push(N);
  map[N] = 1;

  while (!queue.empty())
  {
    const int place = queue.top();
    const int count = map[place];
    const int left_place = (place-1) / 2;
    const int right_place = place / 2;

    queue.pop();

    std::cerr << place << ' ' << count << ' ' << persons << '\n';

    if (persons + count >= K)
    {
      return std::make_pair(right_place, left_place);
    }

    persons += count;

    if (map.find(left_place) == map.end())
    {
      map[left_place] = 0;
      queue.push(left_place);
    }

    if (map.find(right_place) == map.end())
    {
      map[right_place] = 0;
      queue.push(right_place);
    }

    map[left_place] += count;
    map[right_place] += count;
  }

  return std::make_pair(-1, -1);
}


int main(void)
{
  auto r = f(1000, 1);
  std::cout << r.first << ' ' << r.second << '\n';

  return 0;
}
