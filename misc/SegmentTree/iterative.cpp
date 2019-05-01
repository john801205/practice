#include <cassert>
#include <vector>

class SegmentTree
{
  public:
    SegmentTree(const std::vector<int> &array)
      :_tree{}, _n{array.size()}
    {
      if (_n == 0)
        return;

      _tree.resize(_n * 2);

      for (std::vector<int>::size_type i = 0; i < array.size(); i++)
        _tree[_n+i] = array[i];

      for (std::vector<int>::size_type i = _n-1; i > 0; i--)
        _tree[i] = _tree[i*2] + _tree[i*2+1];
    }

    void update(const std::vector<int>::size_type index,
                const int                         value)
    {
      if (index >= _n)
        return;

      _tree[_n+index] = value;
      for (auto i = (_n+index) / 2; i > 0; i >>= 1)
        _tree[i] = _tree[i*2] + _tree[i*2+1];
    }

    int query(std::vector<int>::size_type l, std::vector<int>::size_type r)
    {
      if (l >= _n)
        return 0;
      if (r >= _n)
        r = _n;

      int res = 0;
      for (auto i = _n+l, j = _n+r; i < j; i >>= 1, j >>= 1)
      {
        if (i & 1) res += _tree[i++];
        if (j & 1) res += _tree[--j];
      }
      return res;
    }

  private:
    std::vector<int> _tree;
    std::vector<int>::size_type _n;
};

int main(void)
{
  SegmentTree obj ({1,3,5});
  assert(obj.query(0, 3) == 9);
  obj.update(1,2);
  assert(obj.query(0, 3) == 8);
  return 0;
}
