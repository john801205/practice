#include <iostream>
#include <unordered_map>

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
    int rob(TreeNode* root)
    {
      std::unordered_map<TreeNode *, int> map;
      return rob(root, map);
    }

    int rob(TreeNode* root, std::unordered_map<TreeNode *, int> &map)
    {
      if (root == nullptr)
        return 0;

      if (map.find(root) != map.end())
        return map[root];

      int money1 = root->val;
      if (root->left != nullptr)
        money1 += rob(root->left->left, map) + rob(root->left->right, map);
      if (root->right != nullptr)
        money1 += rob(root->right->left, map) + rob(root->right->right, map);

      int money2 = rob(root->left, map) + rob(root->right, map);
      map[root] = std::max(money1, money2);

      return map[root];
    }
};

int main()
{
  return 0;
}
