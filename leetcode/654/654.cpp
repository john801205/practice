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
    TreeNode* constructMaximumBinaryTree(const std::vector<int>& nums)
    {
      if (nums.size() == 0)
        return nullptr;

      return constructMaximumBinaryTree(nums, 0, nums.size()-1);
    }

    TreeNode* constructMaximumBinaryTree(const std::vector<int>            &nums,
                                         const std::vector<int>::size_type  l,
                                         const std::vector<int>::size_type  r)
    {
      if (l > r)
        return nullptr;

      std::vector<int>::size_type maxindex = l;
      for (std::vector<int>::size_type i = l+1; i < r; i++)
        if (nums[i] > nums[maxindex])
          maxindex = i;

      TreeNode *root = new TreeNode (nums[maxindex]);
      root->left = constructMaximumBinaryTree(nums, l, maxindex-1);
      root->right = constructMaximumBinaryTree(nums, maxindex+1, r);

      return root;
    }
};

int main()
{
  return 0;
}
