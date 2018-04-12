#include <cassert>
#include <climits>
#include <iostream>
#include <queue>

class MedianFinder
{
  private:
    std::priority_queue<int> lower;
    std::priority_queue<int, std::vector<int>, std::greater<int>> higher;
    std::priority_queue<int>::size_type count;

  public:
    MedianFinder(): lower(), higher(), count(0)
    {
      lower.emplace(INT_MIN);
      higher.emplace(INT_MAX);
    }

    void addNum(int num)
    {
      if (num >= lower.top())
      {
        higher.emplace(num);

        if (higher.size() > lower.size())
        {
          lower.emplace(higher.top());
          higher.pop();
        }
      }
      else
      {
        lower.emplace(num);

        if (lower.size() > higher.size()+1)
        {
          higher.emplace(lower.top());
          lower.pop();
        }
      }

      count++;
    }

    double findMedian()
    {
      if (count % 2 == 1)
      {
        return lower.top();
      }
      else
      {
        return (lower.top() + higher.top()) / 2.0;
      }
    }
};

int main(void)
{
  MedianFinder obj;
  obj.addNum(1);
  obj.addNum(2);
  assert(obj.findMedian() == 1.5);
  obj.addNum(3);
  assert(obj.findMedian() == 2);
  obj.addNum(-1);
  assert(obj.findMedian() == 1.5);
  obj.addNum(-1);
  assert(obj.findMedian() == 1);
  return 0;
}
