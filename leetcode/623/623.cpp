#include <cassert>
#include <cstddef>

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
    TreeNode* addOneRow(TreeNode* root, int v, int d)
    {
      if (d == 1)
      {
        TreeNode *nroot = new TreeNode(v);
        nroot->left = root;
        return nroot;
      }

      dfs(root, v, d, 1);
      return root;
    }

    void dfs(TreeNode* root, int v, int d, int cur)
    {
      if (root == nullptr)
        return;

      if (cur+1 == d)
      {
        TreeNode *left = new TreeNode(v);
        left->left = root->left;
        root->left = left;

        TreeNode *right = new TreeNode(v);
        right->right = root->right;
        root->right = right;

        return;
      }

      dfs(root->left, v, d, cur+1);
      dfs(root->right, v, d, cur+1);
    }
};

int main()
{
  return 0;
}
