#include <iostream>
#include <unordered_map>
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
    TreeNode* buildTree(const std::vector<int> &inorder, const std::vector<int> &postorder)
    {
      if (inorder.size() == 0)
        return nullptr;

      std::unordered_map<int, std::vector<int>::size_type> map;
      for (std::vector<int>::size_type i = 0; i < inorder.size(); i++)
        map[inorder[i]] = i;

      return buildTree(inorder, 0, inorder.size()-1, postorder, 0, postorder.size()-1, map);
    }

  private:
    TreeNode* buildTree(const std::vector<int> &inorder,
                              int               instart,
                              int               inend,
                        const std::vector<int> &postorder,
                              int               poststart,
                              int               postend,
                        const std::unordered_map<int, std::vector<int>::size_type> &map)
    {
      if (instart > inend || poststart > postend)
        return nullptr;

      TreeNode *node = new TreeNode(postorder[postend]);
      int inindex = map.at(postorder[postend]);

      node->left = buildTree(inorder, instart, inindex-1, postorder, poststart, poststart+inindex-instart-1, map);
      node->right = buildTree(inorder, inindex+1, inend, postorder, poststart+inindex-instart, postend-1, map);

      return node;
    }
};

int main()
{
  return 0;
}
