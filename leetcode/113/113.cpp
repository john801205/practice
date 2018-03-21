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
    std::vector<std::vector<int>> pathSum(TreeNode* root, int sum)
    {
      std::vector<std::vector<int>> result;
      std::vector<int> path;

      dfs(root, sum, path, result);

      return result;
    }

  private:
    void dfs(TreeNode                      *node,
             int                            sum,
             std::vector<int>              &path,
             std::vector<std::vector<int>> &result)
    {
      if (node == nullptr)
      {
        return;
      }

      path.push_back(node->val);

      if (node->left == nullptr && node->right == nullptr && sum == 0)
      {
        result.push_back(path);
      }
      else
      {
        sum -= node->val;
        dfs(node->left, sum, path, result);
        dfs(node->right, sum, path, result);
      }

      path.pop_back();
    }
};

int main(void)
{
  return 0;
}
