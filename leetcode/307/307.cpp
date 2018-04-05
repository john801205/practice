#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

class NumArray
{
  private:
    std::vector<int>            segment_tree;
    std::vector<int>::size_type shift;

    int sumRange(std::vector<int>::size_type current,
                 int current_left,
                 int current_right,
                 int i,
                 int j)
    {
      if (i == current_left && j == current_right)
      {
        return this->segment_tree[current];
      }

      int middle = current_left + (current_right - current_left)/2;

      if (j <= middle)
      {
        return sumRange(current*2+1, current_left, middle, i, j);
      }
      else if (i > middle)
      {
        return sumRange(current*2+2, middle+1, current_right, i, j);
      }
      else
      {
        return sumRange(current*2+1, current_left, middle, i, middle)
               + sumRange(current*2+2, middle+1, current_right, middle+1, j);
      }
    }
  public:
    NumArray(const std::vector<int> &nums): segment_tree(), shift()
    {
      std::vector<int>::size_type depth = std::ceil(std::log2(nums.size()));
      std::vector<int>::size_type size = std::pow(2, depth+1)-1;

      this->shift = std::pow(2, depth)-1;
      this->segment_tree.resize(size);

      for (std::vector<int>::size_type i = 0; i < nums.size(); i++)
      {
        this->segment_tree[i+shift] = nums[i];
      }

      for (std::vector<int>::size_type i = shift; i-- > 0; )
      {
        this->segment_tree[i] = this->segment_tree[i*2+1] + this->segment_tree[i*2+2];
      }
    }

    void update(int i, int val)
    {
      std::vector<int>::size_type current = this->shift + i;
      int difference = val - this->segment_tree[current];

      while (current != 0)
      {
        this->segment_tree[current] += difference;
        current = (current - 1) / 2;
      }

      this->segment_tree[0] += difference;
    }

    int sumRange(int i, int j)
    {
      return sumRange(0, 0, this->shift, i, j);
    }

};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */

int main(void)
{
  NumArray obj ({1,3,5});
  assert(obj.sumRange(0, 2) == 9);
  obj.update(1,2);
  assert(obj.sumRange(0, 2) == 8);
  return 0;
}
