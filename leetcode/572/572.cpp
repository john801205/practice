#include <iostream>

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
  public:
    bool isSubtree(TreeNode* s, TreeNode* t)
    {
      if (s == nullptr && t == nullptr)
        return true;
      else if (s == nullptr || t == nullptr)
        return false;
      else if (s->val== t->val && isEquivalentTree(s, t))
        return true;
      else
        return isSubtree(s->left, t) || isSubtree(s->right, t);
    }

  private:
    bool isEquivalentTree(TreeNode *s, TreeNode *t)
    {
      if (s == nullptr && t == nullptr)
        return true;
      else if (s == nullptr || t == nullptr)
        return false;
      else
        return s->val == t->val
               && isEquivalentTree(s->left, t->left)
               && isEquivalentTree(s->right, t->right);
    }
};

int main()
{
  return 0;
}
