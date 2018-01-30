#include <iostream>
#include <vector>

struct Trie
{
  std::vector<std::size_t> tree;

  Trie (): tree({0, 0}) {}

  void insert(const int num)
  {
    std::size_t index = 0;
    for (int i = 31; i >= 0; i--)
    {
      bool bit = ((num >> i) & 1) == 0x1;

      if (bit)
      {
        if (tree[index] == 0)
        {
          tree[index] = tree.size();
          tree.push_back(0);
          tree.push_back(0);
        }

        index = tree[index];
      }
      else
      {
        if (tree[index+1] == 0)
        {
          tree[index+1] = tree.size();
          tree.push_back(0);
          tree.push_back(0);
        }

        index = tree[index+1];
      }
    }
  }

  int findMax(const int num)
  {
    int result = 0;

    std::size_t index = 0;
    for (int i = 31; i >= 0; i--)
    {
      if (tree[index] == 0 and tree[index+1] == 0)
      {
        result <<= 1;
        continue;
      }

      bool bit = ((num >> i) & 1) == 0x1;

      if (bit)
      {
        if (tree[index+1] != 0)
        {
          index = tree[index+1];
          result <<= 1;
        }
        else
        {
          index = tree[index];
          result <<= 1;
          result |= 1;
        }
      }
      else
      {
        if (tree[index] != 0)
        {
          index = tree[index];
          result <<= 1;
          result |= 1;
        }
        else
        {
          index = tree[index+1];
          result <<= 1;
        }
      }
    }

    return result;
  }
};

int main(void)
{
  int T;

  while (std::cin >> T)
  {
    for (int t = 0; t < T; t++)
    {
      Trie trie;
      int N;
      std::cin >> N;

      int max = 0;

      int current_xor = 0;
      trie.insert(0);

      for (int i = 1; i <= N; i++)
      {
        int number;
        std::cin >> number;

        int xor_ = current_xor ^ number;
        int complement = trie.findMax(xor_);

        if ((complement ^ xor_) > max)
          max = complement ^ xor_;

        trie.insert(xor_);

        current_xor = xor_;
      }

      std::cout << max << '\n';
    }
  }

  return 0;
}
