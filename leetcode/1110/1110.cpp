#include <unordered_set>
#include <vector>

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
    std::vector<TreeNode*> delNodes(TreeNode* root, std::vector<int>& to_delete)
    {
      std::unordered_set<int> set(to_delete.begin(), to_delete.end());
      std::vector<TreeNode *> result;

      dfs(root, set, result, true);

      return result;
    }

    TreeNode *dfs(TreeNode *root,
        const std::unordered_set<int> &set,
        std::vector<TreeNode *> &result,
        bool newroot)
    {
      if (root == nullptr)
        return nullptr;

      bool deleted = (set.find(root->val) != set.end());
      if (newroot && !deleted)
        result.emplace_back(root);

      root->left = dfs(root->left, set, result, deleted);
      root->right = dfs(root->right, set, result, deleted);

      if (deleted)
        return nullptr;
      return root;
    }
};

int main()
{
  return 0;
}
