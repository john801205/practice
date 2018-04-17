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
    std::vector<TreeNode*> generateTrees(int n)
    {
      std::vector<std::vector<std::vector<TreeNode *>>> dp (n+2, std::vector<std::vector<TreeNode *>> (n+2, std::vector<TreeNode *> (1, nullptr)));

      dp[1][n].clear();
      for (int len = 0; len < n; len++)
      {
        for (int i = 1; i+len <= n; i++)
        {
          int j = i+len;

          dp[i][j].clear();
          for (int k = i; k <= j; k++)
          {
            for (const auto &left: dp[i][k-1])
            {
              for (const auto &right: dp[k+1][j])
              {
                TreeNode *root = new TreeNode(k);
                root->left = left;
                root->right = right;

                dp[i][j].emplace_back(root);
              }
            }
          }
        }
      }

      return dp[1][n];
    }
};

int main(void)
{
  Solution s;
  auto r = s.generateTrees(3);
  return 0;
}
