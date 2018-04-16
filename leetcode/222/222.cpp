#include <cmath>
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
    int countNodes(TreeNode* root)
    {
      if (root == nullptr)
        return 0;

      int hl = getHeight(root->left);
      int hr = getHeight(root->right);

      if (hl == hr)
        return std::pow(2, hl) + countNodes(root->right);
      else
        return countNodes(root->left) + std::pow(2, hr);
    }

    int getHeight(TreeNode *root)
    {
      int h = 0;

      while (root != nullptr)
      {
        h++;
        root = root->left;
      }

      return h;
    }
};

int main(void)
{
  return 0;
}
