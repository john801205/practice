#include <cassert>
#include <climits>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

class RangeModule
{
  public:
    RangeModule(): _intervals{}
    {
    }

    void addRange(int left, int right)
    {
      auto first = _intervals.lower_bound(left);
      if (first != _intervals.begin() && std::prev(first)->second >= left)
        first = std::prev(first);
      int begin = left;
      if (first != _intervals.end())
        begin = std::min(begin, first->first);

      auto last = first;
      int end = right;
      while (last != _intervals.end() && last->first <= right)
      {
        end = std::max(end, last->second);
        last = std::next(last);
      }

      _intervals.erase(first, last);
      _intervals[begin] = end;
    }

    bool queryRange(int left, int right)
    {
      auto first = _intervals.lower_bound(left);
      if (first != _intervals.begin() && std::prev(first)->second > left)
        first = std::prev(first);

      return first != _intervals.end() && first->first <= left && first->second >= right;
    }

    void removeRange(int left, int right)
    {
      auto first = _intervals.lower_bound(left);
      if (first != _intervals.begin() && std::prev(first)->second > left)
        first = std::prev(first);

      auto last = first;
      while (last != _intervals.end() && last->first < right)
        last = std::next(last);

      std::vector<std::pair<int,int>> todo;
      if (first != _intervals.end() && first->first <= left)
        todo.push_back({first->first, left});

      if (last != _intervals.begin() && std::prev(last)->second >= right)
        todo.push_back({right, std::prev(last)->second});

      _intervals.erase(first, last);

      for (const auto &v: todo)
        _intervals[v.first] = v.second;
    }

  private:
    std::map<int, int> _intervals;
};

int main()
{
  RangeModule* obj = new RangeModule();
  assert(obj->queryRange(1,4) == false);
  assert(obj->queryRange(6,10) == false);
  obj->addRange(2,6);
  obj->addRange(2,8);
  obj->addRange(4,7);
  assert(obj->queryRange(2,5) == true);
  delete obj;

  obj = new RangeModule();
  obj->addRange(10,20);
  obj->removeRange(14,16);
  assert(obj->queryRange(10,14) == true);
  assert(obj->queryRange(13,15) == false);
  assert(obj->queryRange(16,17) == true);
  delete obj;

  return 0;
}
