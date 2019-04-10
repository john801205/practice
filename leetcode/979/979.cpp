#include <cassert>
#include <cmath>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution
{
  public:
    int distributeCoins(TreeNode* root)
    {
      int moves = 0;
      dfs(root, moves);
      return moves;
    }

    int dfs(TreeNode *node, int &moves)
    {
      if (node == nullptr)
        return 0;

      int value = node->val;
      value -= dfs(node->left, moves);
      value -= dfs(node->right, moves);
      moves += std::abs(1 - value);

      return 1 - value;
    }
};

int main()
{
  Solution s;

  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(0);
  root->right = new TreeNode(0);
  root->left->right = new TreeNode(3);
  assert(s.distributeCoins(root) == 4);

  root = new TreeNode(3);
  root->left = new TreeNode(0);
  root->right = new TreeNode(0);
  assert(s.distributeCoins(root) == 2);

  root = new TreeNode(0);
  root->left = new TreeNode(3);
  root->right = new TreeNode(0);
  assert(s.distributeCoins(root) == 3);
  return 0;
}
