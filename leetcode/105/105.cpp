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
    TreeNode* buildTree(const std::vector<int> &preorder,
                        const std::vector<int> &inorder)
    {
      if (inorder.size() == 0)
        return nullptr;

      std::unordered_map<int, std::vector<int>::size_type> map;
      for (std::vector<int>::size_type i = 0; i < inorder.size(); i++)
        map[inorder[i]] = i;

      return buildTree(preorder, 0, inorder, 0, inorder.size()-1, map);
    }

  private:
    TreeNode* buildTree(const std::vector<int>            &preorder,
                              std::vector<int>::size_type  preindex,
                        const std::vector<int>            &inorder,
                              int  instart,
                              int  inend,
                        const std::unordered_map<int, std::vector<int>::size_type> &map)
    {
      if (preindex >= preorder.size() || instart > inend)
        return nullptr;

      TreeNode *current = new TreeNode (preorder[preindex]);
      std::vector<int>::size_type inindex = map.at(preorder[preindex]);

      current->left = buildTree(preorder, preindex+1, inorder, instart, inindex-1, map);
      current->right = buildTree(preorder, preindex+inindex-instart+1, inorder, inindex+1, inend, map);

      return current;
    }
};

int main()
{
  return 0;
}
