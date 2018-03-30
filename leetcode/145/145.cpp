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
      std::vector<int>        results;
      std::stack<TreeNode *>  stack;
      TreeNode               *current;
      TreeNode               *last;

      current = root;
      last    = nullptr;

      while (current != nullptr || !stack.empty())
      {
        if (current != nullptr)
        {
          stack.push(current);
          current = current->left;
        }
        else
        {
          TreeNode *top = stack.top();

          if (top->right != last)
          {
            current = top->right;
          }
          else
          {
            results.emplace_back(top->val);
            last = top;
            stack.pop();
          }
        }
      }

      return results;
    }
};

int main(void)
{
  return 0;
}
