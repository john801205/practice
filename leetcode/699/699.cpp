#include <cassert>
#include <climits>
#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

class SegmentTree
{
  public:
    SegmentTree(const std::vector<int>::size_type size)
      :_tree{}, _lazy{}, _size{size}
    {
      _tree.resize(4*_size);
      std::fill(_tree.begin(), _tree.end(), 0);

      _lazy.resize(4*_size);
      std::fill(_lazy.begin(), _lazy.end(), 0);
    }

    SegmentTree(const std::vector<int> &nums)
      :_tree{}, _lazy{}, _size{nums.size()}
    {
      if (_size == 0)
        return;

      _tree.resize(4*_size);
      build(nums, 0, 0, _size-1);

      _lazy.resize(4*_size);
      std::fill(_lazy.begin(), _lazy.end(), 0);
    }

    int query(std::vector<int>::size_type left,
              std::vector<int>::size_type right)
    {
      if (_size == 0)
        return INT_MIN;

      return query(0, 0, _size-1, left, right);
    }

    void update(std::vector<int>::size_type left,
                std::vector<int>::size_type right,
                int value)
    {
      if (_size == 0)
        return;

      update(0, 0, _size-1, left, right, value);
    }

  private:
    std::vector<int> _tree, _lazy;
    std::vector<int>::size_type _size;

    void build(const std::vector<int> &nums,
               const std::vector<int>::size_type i,
               const std::vector<int>::size_type left,
               const std::vector<int>::size_type right)
    {
      if (left == right)
      {
        _tree[i] = nums[left];
        return;
      }

      const auto middle = left + (right - left) / 2;
      build(nums, 2*i+1, left, middle);
      build(nums, 2*i+2, middle+1, right);
      _tree[i] = std::max(_tree[2*i+1], _tree[2*i+2]);
    }

    int query(const std::vector<int>::size_type i,
              const std::vector<int>::size_type left,
              const std::vector<int>::size_type right,
              const std::vector<int>::size_type qleft,
              const std::vector<int>::size_type qright)
    {
      updateLazy(i, left, right);

      if (left > qright || right < qleft)
        return INT_MIN;

      if (left >= qleft && right <= qright)
        return _tree[i];

      const auto middle = left + (right - left) / 2;
      int q1 = query(2*i+1, left, middle, qleft, qright);
      int q2 = query(2*i+2, middle+1, right, qleft, qright);

      return std::max(q1, q2);
    }

    void update(const std::vector<int>::size_type i,
                const std::vector<int>::size_type left,
                const std::vector<int>::size_type right,
                const std::vector<int>::size_type qleft,
                const std::vector<int>::size_type qright,
                const int value)
    {
      updateLazy(i, left, right);

      if (left > qright || right < qleft)
        return;

      if (left >= qleft && right <= qright)
      {
        _tree[i] = value;

        if (left != right)
        {
          _lazy[2*i+1] = value;
          _lazy[2*i+2] = value;
        }

        return;
      }

      const auto middle = left + (right - left) / 2;
      update(i*2+1, left, middle, qleft, qright, value);
      update(i*2+2, middle+1, right, qleft, qright, value);

      _tree[i] = std::max(_tree[2*i+1], _tree[2*i+2]);
    }

    void updateLazy(const std::vector<int>::size_type i,
                    const std::vector<int>::size_type left,
                    const std::vector<int>::size_type right)
    {
      if (_lazy[i] != 0)
      {
        _tree[i] = _lazy[i];

        if (left != right)
        {
          _lazy[2*i+1] = _lazy[i];
          _lazy[2*i+2] = _lazy[i];
        }

        _lazy[i] = 0;
      }
    }
};

class Solution
{
  public:
    std::vector<int> fallingSquares(const std::vector<std::vector<int>> &positions)
    {
      auto indexes = coordinateCompress(positions);
      SegmentTree tree(indexes.size());

      std::vector<int> ans(positions.size());

      for (std::vector<int>::size_type i = 0; i < positions.size(); i++)
      {
        const auto &pos = positions[i];
        const auto left = indexes[pos[0]];
        const auto right = indexes[pos[0]+pos[1]-1];

        const auto maxHeight = tree.query(left, right) + pos[1];
        tree.update(left, right, maxHeight);

        if (i == 0)
          ans[i] = maxHeight;
        else
          ans[i] = std::max(ans[i-1], maxHeight);
      }

      return ans;
    }

  private:
    std::unordered_map<int, std::vector<int>::size_type>
      coordinateCompress(const std::vector<std::vector<int>> &positions)
    {
      std::set<int> set;
      for (const auto &pos: positions)
      {
        set.emplace(pos[0]);
        set.emplace(pos[0]+pos[1]-1);
      }

      std::vector<int> axis(set.begin(), set.end());
      std::unordered_map<int, std::vector<int>::size_type> indexes;
      for (std::vector<int>::size_type i = 0; i < axis.size(); i++)
        indexes[axis[i]] = i;

      return indexes;
    }
};

int main()
{
  Solution s;
  assert(s.fallingSquares({{9,7},{1,9},{3,1}}) == std::vector<int>({7,16,17}));
  assert(s.fallingSquares({{1,2},{2,3},{6,1}}) == std::vector<int>({2,5,5}));
  assert(s.fallingSquares({{100,100},{200,100}}) == std::vector<int>({100,100}));
  assert(s.fallingSquares({{1,2},{3,3},{2,2}}) == std::vector<int>({2,3,5}));
  return 0;
}
