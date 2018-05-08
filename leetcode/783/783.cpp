#include <climits>
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
    int minDiffInBST(TreeNode* root)
    {
      long min = INT_MAX, prev = INT_MIN;
      dfs(root, min, prev);
      return min;
    }

    void dfs(TreeNode *root, long &min, long &prev)
    {
      if (root == nullptr)
        return;

      dfs(root->left, min, prev);
      min = std::min(min, root->val - prev);
      prev = root->val;
      dfs(root->right, min, prev);
    }
};

int main()
{
  return 0;
}
