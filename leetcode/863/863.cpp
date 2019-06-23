#include <cassert>
#include <iostream>
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
    std::vector<int> distanceK(TreeNode* root, TreeNode* target, int K)
    {
      std::vector<TreeNode *> path;
      findPath(root, target, path);

      std::vector<int> res;
      TreeNode *prev = nullptr;
      for (int i = 0; i < path.size(); i++)
      {
        const auto &cur = path[i];

        if (i == K)
        {
          res.emplace_back(cur->val);
        }
        else if (i < K)
        {
          if (cur->left != prev)
            findDistanceK(res, cur->left, i+1, K);
          if (cur->right != prev)
            findDistanceK(res, cur->right, i+1, K);
        }
        else
        {
          break;
        }

        prev = path[i];
      }

      return res;
    }

    bool findPath(TreeNode *root, TreeNode *target, std::vector<TreeNode *> &path)
    {
      if (root == nullptr)
        return false;

      if (root == target)
      {
        path.emplace_back(root);
        return true;
      }

      bool found = findPath(root->left, target, path);
      if (found)
      {
        path.emplace_back(root);
        return true;
      }

      found = findPath(root->right, target, path);
      if (found)
      {
        path.emplace_back(root);
        return true;
      }

      return false;
    }

    void findDistanceK(std::vector<int> &res, TreeNode *root, int distance, int K)
    {
      if (root == nullptr || distance > K)
        return;

      if (distance == K)
      {
        res.emplace_back(root->val);
        return;
      }

      findDistanceK(res, root->left, distance+1, K);
      findDistanceK(res, root->right, distance+1, K);
    }
};

int main()
{
  Solution s;

  TreeNode node0(0), node1(1), node2(2), node3(3), node4(4);
  TreeNode node5(5), node6(6), node7(7), node8(8);

  node2.left = &node7, node2.right = &node4;
  node5.left = &node6, node5.right = &node2;
  node1.left = &node0, node1.right = &node8;
  node3.left = &node5, node3.right = &node1;

  assert(s.distanceK(&node3, &node5, 4) == std::vector<int>({}));
  assert(s.distanceK(&node3, &node5, 3) == std::vector<int>({0,8}));
  assert(s.distanceK(&node3, &node5, 2) == std::vector<int>({7,4,1}));
  assert(s.distanceK(&node3, &node5, 1) == std::vector<int>({6,2,3}));
  assert(s.distanceK(&node3, &node5, 0) == std::vector<int>({5}));

  return 0;
}
