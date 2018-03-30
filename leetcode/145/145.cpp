#include <iostream>
#include <stack>
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
    std::vector<int> postorderTraversal(TreeNode* root)
    {
      std::vector<int>       results;
      std::stack<TreeNode *> stack;
      std::stack<bool>       status;

      stack.push(root);
      status.push(false);

      while (!stack.empty())
      {
        TreeNode *current  = stack.top();
        bool      explored = status.top();

        stack.pop();
        status.pop();

        if (current == nullptr)
        {
          continue;
        }

        if (explored)
        {
          results.emplace_back(current->val);
        }
        else
        {
          stack.push(current);
          status.push(true);

          stack.push(current->right);
          status.push(false);

          stack.push(current->left);
          status.push(false);
        }
      }

      return results;
    }
};

int main(void)
{
  return 0;
}
