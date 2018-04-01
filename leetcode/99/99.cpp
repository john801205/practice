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
    void recoverTree(TreeNode* root)
    {
      TreeNode *current  = root;
      TreeNode *previous = nullptr;
      TreeNode *first    = nullptr;
      TreeNode *second   = nullptr;

      while (current != nullptr)
      {
        if (current->left == nullptr)
        {
          if (previous != nullptr && current->val < previous->val)
          {
            if (first == nullptr)
            {
              first = previous;
            }

            second = current;
          }

          previous = current;
          current = current->right;
        }
        else
        {
          TreeNode *predecessor = current->left;

          while (predecessor->right != nullptr && predecessor->right != current)
          {
            predecessor = predecessor->right;
          }

          if (predecessor->right == nullptr)
          {
            predecessor->right = current;
            current = current->left;
          }
          else
          {
            predecessor->right = nullptr;

            if (previous != nullptr && current->val < previous->val)
            {
              if (first == nullptr)
              {
                first = previous;
              }

              second = current;
            }

            previous = current;
            current = current->right;
          }
        }
      }

      if (first != nullptr)
      {
        std::swap(first->val, second->val);
      }
    }
};

int main(void)
{
  TreeNode root(0);
  root.left = new TreeNode(1);
  Solution s;
  s.recoverTree(&root);
  return 0;
}
