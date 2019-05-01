#include <cassert>
#include <vector>

class FenwickTree
{
  public:
    FenwickTree(const std::vector<int> &array)
      :_tree{}, _n{array.size()}
    {
      _tree.resize(array.size()+1);
      for (std::vector<int>::size_type i = 1; i <= array.size(); i++)
      {
        _tree[i] += array[i-1];

        auto j = i + (i & -i);
        if (j <= _n)
          _tree[j] += _tree[i];
      }
    }

    void add(const std::vector<int>::size_type index,
             const int                         value)
    {
      for (auto i = index+1; i <= _n; i += i&-i)
        _tree[i] += value;
    }

    int query(std::vector<int>::size_type r)
    {
      if (r >= _n)
        r = _n-1;

      int res = 0;
      for (auto i = r+1; i > 0; i -= i&-i)
        res += _tree[i];

      return res;
    }

    int query(std::vector<int>::size_type l, std::vector<int>::size_type r)
    {
      if (l >= _n)
        return 0;

      if (l > 0)
        return query(r) - query(l-1);
      else
        return query(r);
    }

  private:
    std::vector<int> _tree;
    std::vector<int>::size_type _n;
};

int main(void)
{
  FenwickTree obj ({1,3,5,7,9,11});
  assert(obj.query(0, 5) == 36);
  obj.add(1,-1);
  assert(obj.query(0, 5) == 35);
  assert(obj.query(1, 5) == 34);
  return 0;
}
