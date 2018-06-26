#include <cassert>
#include <iostream>
#include <vector>

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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
      std::vector<TreeNode *> pParents, qParents;

      findAncestors(root, p, pParents);
      findAncestors(root, q, qParents);

      TreeNode *ancestor = nullptr;
      for (std::vector<TreeNode *>::size_type i = 0; i < pParents.size() && i < qParents.size(); i++)
      {
        if (pParents[i] != qParents[i])
          continue;
        else
          ancestor = pParents[i];
      }

      return ancestor;
    }

  private:
    bool findAncestors(TreeNode *root,
                   TreeNode *p,
                   std::vector<TreeNode *> &ancestors)
    {
      if (root == nullptr)
        return false;

      ancestors.emplace_back(root);
      if (root == p)
        return true;

      bool found = findAncestors(root->left, p, ancestors);
      if (found)
        return true;

      found = findAncestors(root->right, p, ancestors);
      if (found)
        return true;

      ancestors.pop_back();
      return false;
    }
};

int main()
{
  TreeNode *node7 = new TreeNode(7);
  TreeNode *node4 = new TreeNode(4);
  TreeNode *node2 = new TreeNode(2);
  node2->left = node7;
  node2->right = node4;

  TreeNode *node6 = new TreeNode(6);
  TreeNode *node5 = new TreeNode(5);
  node5->left = node6;
  node5->right = node2;

  TreeNode *node0 = new TreeNode(0);
  TreeNode *node8 = new TreeNode(8);
  TreeNode *node1 = new TreeNode(1);
  node1->left = node0;
  node1->right = node8;

  TreeNode *node3 = new TreeNode(3);
  node3->left = node5;
  node3->right = node1;

  Solution s;
  assert(s.lowestCommonAncestor(node3, node5, node1)->val == 3);
  assert(s.lowestCommonAncestor(node3, node5, node4)->val == 5);
  assert(s.lowestCommonAncestor(node3, node7, node8)->val == 3);
  return 0;
}
