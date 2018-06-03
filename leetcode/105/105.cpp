#include <iostream>
#include <unordered_set>
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
    TreeNode* buildTree(const std::vector<int> &preorder,
                        const std::vector<int> &inorder)
    {
      if (inorder.size() == 0)
        return nullptr;

      std::vector<int>::size_type preindex = 0, inindex = 0;
      std::unordered_set<int> stack;
      return buildTree(preorder, preindex, inorder, inindex, stack);
    }

  private:
    TreeNode* buildTree(const std::vector<int>            &preorder,
                              std::vector<int>::size_type &preindex,
                        const std::vector<int>            &inorder,
                              std::vector<int>::size_type &inindex,
                              std::unordered_set<int>     &stack)
    {
      if (preindex >= preorder.size())
        return nullptr;

      TreeNode *current = new TreeNode (preorder[preindex]);
      stack.emplace(current->val);
      preindex++;

      if (current->val != inorder[inindex])
        current->left = buildTree(preorder, preindex, inorder, inindex, stack);

      inindex++;

      if (inindex < inorder.size() && stack.find(inorder[inindex]) == stack.end())
        current->right = buildTree(preorder, preindex, inorder, inindex, stack);

      stack.erase(current->val);

      return current;
    }
};

int main()
{
  return 0;
}
