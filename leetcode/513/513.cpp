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
    int findBottomLeftValue(TreeNode* root)
    {
      int max_depth = -1;
      int left_value = 0;
      dfs(root, 0, max_depth, left_value);
      return left_value;
    }

  private:
    void dfs(TreeNode *root, int depth, int &max_depth, int &left_value)
    {
      if (root == nullptr)
        return;

      if (depth > max_depth)
      {
        max_depth = depth;
        left_value = root->val;
      }

      dfs(root->left, depth+1, max_depth, left_value);
      dfs(root->right, depth+1, max_depth, left_value);
    }

};

int main()
{
  Solution s;
  TreeNode *root = new TreeNode(2);
  root->left = new TreeNode(1);
  root->right = new TreeNode(3);
  assert(s.findBottomLeftValue(root) == 1);

  root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->left->left = new TreeNode(4);
  root->right = new TreeNode(3);
  root->right->left = new TreeNode(5);
  root->right->left->left = new TreeNode(7);
  root->right->right = new TreeNode(6);
  assert(s.findBottomLeftValue(root) == 7);

  return 0;
}
