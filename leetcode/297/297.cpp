#include <cassert>
#include <iostream>
#include <queue>
#include <string>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec
{
  public:
    // Encodes a tree to a single string.
    std::string serialize(TreeNode* root)
    {
      std::queue<TreeNode*> queue ({root});
      std::string           result;
      bool                  first = true;

      while (!queue.empty())
      {
        if (!first)
          result += ',';
        first = false;

        TreeNode *current = queue.front();
        queue.pop();

        if (current != nullptr)
        {
          result += std::to_string(current->val);
          queue.emplace(current->left);
          queue.emplace(current->right);
        }
      }

      auto pos = result.find_last_not_of(',');
      if (pos != std::string::npos)
        result.erase(pos+1);

      return result;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(const std::string data)
    {
      TreeNode                *root = nullptr;
      std::queue<TreeNode **>  queue ({&root});
      std::string::size_type   pos  = 0;


      while (!queue.empty() && pos < data.size())
      {
        TreeNode **current = queue.front();
        queue.pop();

        std::string val;
        while (pos < data.size() && data[pos] != ',')
        {
          val += data[pos];
          pos++;
        }

        if (pos < data.size())
          pos++;

        if (val != "")
        {
          *current = new TreeNode(std::stoi(val));

          queue.emplace(&((*current)->left));
          queue.emplace(&((*current)->right));
        }
      }

      return root;
    }
};

int main(void)
{
  // Your Codec object will be instantiated and called as such:
  Codec codec;

  TreeNode *root = new TreeNode(1);
  root->right = new TreeNode(3);
  root->right->left = new TreeNode(5);
  root->right->right = new TreeNode(7);
  TreeNode *result = codec.deserialize(codec.serialize(root));

  assert(result->val == 1);
  assert(result->left == nullptr);
  assert(result->right != nullptr);
  assert(result->right->val == 3);
  assert(result->right->left != nullptr);
  assert(result->right->right != nullptr);
  assert(result->right->left->val == 5);
  assert(result->right->right->val == 7);

  result = codec.deserialize(codec.serialize(nullptr));
  assert(result == nullptr);
  return 0;
}
