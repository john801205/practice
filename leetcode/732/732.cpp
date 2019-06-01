#include <cassert>
#include <algorithm>
#include <iostream>

class SegmentNode
{
  public:
    int value;
    int lazy;
    SegmentNode *left, *right;

    SegmentNode(int value): value{value}, lazy{0}, left{nullptr}, right{nullptr}
    {
    }

    ~SegmentNode()
    {
      if (left != nullptr) delete left;
      if (right != nullptr) delete right;
    }
};

class SegmentTree
{
  public:
    SegmentTree(): _root{nullptr}
    {
      _root = new SegmentNode(0);
    }

    ~SegmentTree()
    {
      delete _root;
    }

    int update(int start, int end)
    {
      return update(_root, 0, 1000000001, start, end);
    }

  private:
    SegmentNode *_root;

    int update(SegmentNode *root, int start, int end, int qstart, int qend)
    {
      if (start > qend || end < qstart)
        return 0;

      if (root->lazy != 0)
      {
        root->value += root->lazy;

        if (start != end)
        {
          if (root->left == nullptr) root->left = new SegmentNode(0);
          if (root->right == nullptr) root->right = new SegmentNode(0);
          root->left->lazy += root->lazy;
          root->right->lazy += root->lazy;
        }

        root->lazy = 0;
      }

      if (start >= qstart && end <= qend)
      {
        root->value += 1;
        if (start != end)
        {
          if (root->left == nullptr) root->left = new SegmentNode(0);
          if (root->right == nullptr) root->right = new SegmentNode(0);
          root->left->lazy += 1;
          root->right->lazy += 1;
        }

        return root->value;
      }

      const auto middle = start + (end - start) / 2;
      if (root->left == nullptr) root->left = new SegmentNode(0);
      if (root->right == nullptr) root->right = new SegmentNode(0);
      const auto q1 = update(root->left, start, middle, qstart, qend);
      const auto q2 = update(root->right, middle+1, end, qstart, qend);
      root->value = std::max(root->value, std::max(q1, q2));
      return root->value;
    }
};

class MyCalendarThree
{
  public:
    MyCalendarThree(): _tree{}
    {
    }

    int book(int start, int end)
    {
      return _tree.update(start, end-1);
    }

  private:
    SegmentTree _tree;
};

int main()
{
  MyCalendarThree* obj = new MyCalendarThree();
  assert(1 == obj->book(10,20));
  assert(1 == obj->book(50,60));
  assert(2 == obj->book(10,40));
  assert(3 == obj->book(5,15));
  assert(3 == obj->book(5,10));
  assert(3 == obj->book(25,55));
  assert(3 == obj->book(925,955));
  assert(4 == obj->book(9,955));
  delete obj;
  return 0;
}
