#include <cassert>
#include <map>
#include <set>
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
    std::vector<std::vector<int>> verticalTraversal(TreeNode* root)
    {
      std::map<int, std::map<int, std::multiset<int>, std::greater<int>>> map;
      helper(root, map, 0, 0);

      std::vector<std::vector<int>> res;
      for (const auto &[x, vertical]: map)
      {
        std::vector<int> temp;
        for (const auto &[y, val]: vertical)
        {
          temp.insert(temp.end(), val.begin(), val.end());
        }
        res.emplace_back(temp);
      }

      return res;
    }

  private:
    void helper(TreeNode *root,
                std::map<int, std::map<int, std::multiset<int>, std::greater<int>>> &map,
                int x, int y)
    {
      if (root == nullptr)
        return;

      map[x][y].emplace(root->val);
      helper(root->left, map, x-1, y-1);
      helper(root->right, map, x+1, y-1);
    }
};

int main()
{
  Solution s;
  {
    TreeNode root(3), l1(9), r1(20), r11(15), r12(7);
    root.left = &l1;
    root.right = &r1;
    r1.left = &r11;
    r1.right = &r12;
    assert(s.verticalTraversal(&root) == std::vector<std::vector<int>>({{9}, {3,15},{20},{7}}));
  }

  {
    TreeNode root(1), l1(2), r1(3), l11(4), l12(5), r11(6), r12(7);
    root.left = &l1;
    root.right = &r1;
    l1.left = &l11;
    l1.right = &l12;
    r1.left = &r11;
    r1.right = &r12;
    assert(s.verticalTraversal(&root) == std::vector<std::vector<int>>({{4},{2},{1,5,6},{3},{7}}));
  }


  return 0;
}
