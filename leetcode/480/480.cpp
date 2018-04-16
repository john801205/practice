#include <cassert>
#include <climits>
#include <iostream>
#include <vector>

class PriorityQueue
{
  private:
    std::vector<long> data;

    std::vector<long>::size_type parent(std::vector<long>::size_type pos)
    {
      return (pos-1) / 2;
    }

    std::vector<long>::size_type left(std::vector<long>::size_type pos)
    {
      return 2*pos + 1;
    }

    std::vector<long>::size_type right(std::vector<long>::size_type pos)
    {
      return 2*pos + 2;
    }

  public:
    PriorityQueue(): data() {}

    void push(long num)
    {
      data.emplace_back(num);

      std::vector<long>::size_type pos = data.size()-1;

      while (pos != 0 && data[pos] > data[parent(pos)])
      {
        std::swap(data[pos], data[parent(pos)]);
        pos = parent(pos);
      }
    }

    long top()
    {
      return data.front();
    }

    void pop()
    {
      std::swap(data.front(), data.back());
      data.pop_back();

      std::vector<long>::size_type pos = 0;
      while (true)
      {
        long max = data[pos];
        auto maxpos = pos;

        if (left(pos) < data.size() && data[left(pos)] > max)
        {
          max = data[left(pos)];
          maxpos = left(pos);
        }

        if (right(pos) < data.size() && data[right(pos)] > max)
        {
          max = data[right(pos)];
          maxpos = right(pos);
        }

        if (maxpos == pos)
          break;

        std::swap(data[pos], data[maxpos]);
        pos = maxpos;
      }
    }

    void add(std::vector<long>::size_type pos, long val)
    {
      data[pos] += val;

      while (pos != 0 && data[pos] > data[parent(pos)])
      {
        std::swap(data[pos], data[parent(pos)]);
        pos = parent(pos);
      }
    }

    void erase(long num)
    {
      for (std::vector<long>::size_type i = 0; i < data.size(); i++)
      {
        if (data[i] == num)
        {
          add(i, INT_MAX - num);
          pop();
          break;
        }
      }
    }

    std::vector<long>::size_type size()
    {
      return data.size();
    }
};

class Solution
{
  public:
    std::vector<double> medianSlidingWindow(const std::vector<int> &nums, const int k)
    {
      if (nums.size() == 0)
        return {};

      PriorityQueue small, large;
      std::vector<double> result;

      for (int i = 0; i < nums.size(); i++)
      {
        small.push(nums[i]);
        large.push(-small.top());
        small.pop();

        if (small.size() < large.size())
        {
          small.push(-large.top());
          large.pop();
        }

        if (i >= k-1)
        {
          double median = (k % 2 == 0 ? (small.top() - large.top()) / 2.0: small.top());
          result.emplace_back(median);

          if (nums[i-k+1] > median)
            large.erase(-nums[i-k+1]);
          else
            small.erase(nums[i-k+1]);
        }
      }

      return result;
    }
};

int main(void)
{
  PriorityQueue q;
  q.push(1);
  assert(q.top() == 1);
  q.pop();
  q.push(5);
  q.push(4);
  q.push(3);
  q.push(2);
  q.push(1);
  assert(q.top() == 5);
  q.pop();
  assert(q.top() == 4);
  q.pop();
  q.erase(3);
  q.erase(2);
  assert(q.size() == 1);
  assert(q.top() == 1);
  q.pop();

  Solution s;
  assert(s.medianSlidingWindow({1,3,-1,-3,5,3,6,7}, 1) == std::vector<double> ({1.0,3.0,-1.0,-3.0,5.0,3.0,6.0,7.0}));
  assert(s.medianSlidingWindow({1,3,-1,-3,5,3,6,7}, 3) == std::vector<double> ({1,-1,-1,3,5,6}));
  assert(s.medianSlidingWindow({1,3,-1,-3,5,3,6,7}, 4) == std::vector<double> ({0.0,1.0,1.0,4.0,5.5}));
  assert(s.medianSlidingWindow({2147483647,2147483647}, 2) == std::vector<double> ({2147483647.0}));
  assert(s.medianSlidingWindow({5,2,2,7,3,7,9,0,2,3}, 9) == std::vector<double> ({3.0, 3.0}));
  assert(s.medianSlidingWindow({-2147483648,-2147483648,2147483647,-2147483648,-2147483648,-2147483648,2147483647,2147483647,2147483647,2147483647,-2147483648,2147483647,-2147483648},3) == std::vector<double> ({-2147483648.0,-2147483648.0,-2147483648.0,-2147483648.0,-2147483648.0,2147483647.0,2147483647.0,2147483647.0,2147483647.0,2147483647.0,-2147483648.0}));

  return 0;
}
