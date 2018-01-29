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

      // array[i] stores a_0 ^ a_1 ^ a_2 ^ ... ^ a_i
      // a_0 = 0
      int *array = new int[N+1];

      array[0] = 0;
      trie.insert(0);
      for (int i = 1; i <= N; i++)
      {
        std::cin >> array[i];
        array[i] = array[i] ^ array[i-1];
        trie.insert(array[i]);
      }

      int max = 0;

      for (int i = 0; i <= N; i++)
      {
        int complement = trie.findMax(array[i]);

        if ((array[i] ^ complement) > max)
          max = array[i] ^ complement;
      }

      std::cout << max << '\n';

      delete[] array;
    }
  }

  return 0;
}
