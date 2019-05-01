#include <cassert>
#include <cmath>
#include <vector>

class SegmentTree
{
  public:
    SegmentTree(const std::vector<int> &array):
      _tree{}, _size(array.size())
    {
      if (array.size() == 0)
        return;

      std::vector<int>::size_type depth = std::ceil(std::log2(array.size()));
      _tree.resize(std::pow(2, depth+1) - 1);
      build(array, 0, array.size()-1, 0);
    }

    void update(const std::vector<int>::size_type index,
                const int value)
    {
      if (index >= _size)
        return;

      int diff = value - query(index, index);
      update(0, _size-1, index, 0, diff);
    }

    int query(const std::vector<int>::size_type start,
              const std::vector<int>::size_type end)
    {
      if (start >= _size)
        return 0;
      return query(0, _size-1, 0, start, end);
    }

  private:
    std::vector<int> _tree;
    std::vector<int>::size_type _size;

    int build(const std::vector<int> &array,
              const std::vector<int>::size_type start,
              const std::vector<int>::size_type end,
              const std::vector<int>::size_type i)
    {
      if (start == end)
      {
        _tree[i] = array[start];
        return _tree[i];
      }

      const auto mid = start + (end - start) / 2;
      _tree[i] = build(array, start, mid, i*2+1) + build(array, mid+1, end, i*2+2);
      return _tree[i];
    }

    int query(const std::vector<int>::size_type start,
              const std::vector<int>::size_type end,
              const std::vector<int>::size_type i,
              const std::vector<int>::size_type qstart,
              const std::vector<int>::size_type qend)
    {
      if (start >= qstart && end <= qend)
        return _tree[i];
      else if (end < qstart || start > qend)
        return 0;

      const auto mid = start + (end - start) / 2;
      return query(start, mid, i*2+1, qstart, qend)
             + query(mid+1, end, i*2+2, qstart, qend);
    }

    void update(const std::vector<int>::size_type start,
                const std::vector<int>::size_type end,
                const std::vector<int>::size_type index,
                const std::vector<int>::size_type i,
                const int diff)
    {
      if (index < start || index > end)
        return;

      _tree[i] += diff;
      if (start == end)
        return;

      const auto mid = start + (end - start) / 2;
      if (index > mid)
        update(mid+1, end, index, i*2+2, diff);
      else
        update(start, mid, index, i*2+1, diff);
    }
};

int main(void)
{
  SegmentTree obj ({1,3,5});
  assert(obj.query(0, 2) == 9);
  obj.update(1,2);
  assert(obj.query(0, 2) == 8);
  return 0;
}
