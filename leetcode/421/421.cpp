#include <vector>

struct TrieNode
{
  TrieNode *children[2];

  TrieNode(): children{} {}

  ~TrieNode()
  {
    for (int i = 0; i < 2; i++)
      if (children[i] != nullptr)
        delete children[i];
  }
};

class Solution
{
  public:
    int findMaximumXOR(const std::vector<int>& nums)
    {
      TrieNode root;
      int result = 0;
      for (const auto &num: nums)
      {
        int value = 0;
        TrieNode *current = &root, *complement = &root;
        for (int i = 31; i >= 0; i--)
        {
          int bit = (num >> i) & 0x1;
          if (current->children[bit] == nullptr)
            current->children[bit] = new TrieNode();
          current = current->children[bit];

          if (complement->children[bit ^ 1] != nullptr)
          {
            value |= 0x1 << i;
            complement = complement->children[bit^1];
          }
          else
          {
            complement = complement->children[bit];
          }
        }

        result = std::max(result, value);
      }

      return result;
    }
};

int main()
{
  return 0;
}
