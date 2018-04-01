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
    int maxPathSum(TreeNode *root)
    {
      int max = INT_MIN;
      dfs(root, max);
      return max;
    }

  private:
    int dfs(TreeNode *root, int &max)
    {
      if (root == nullptr)
      {
        return 0;
      }

      int left  = dfs(root->left, max);
      int right = dfs(root->right, max);

      left = std::max(left, 0);
      right = std::max(right, 0);
      max = std::max(max, left+right+root->val);

      return root->val + std::max(left, right);
    }
};

int main(void)
{
  return 0;
}
