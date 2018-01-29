#include <iostream>

struct Node
{
  Node *left, *right;

  Node (): left(nullptr), right(nullptr) {}
};

struct Trie
{
  Node root;

  Trie (): root() {}

  ~Trie()
  {
    free(&root);
  }

  void free(Node *ptr)
  {
    if (ptr->left != nullptr)
      free(ptr->left);
    delete ptr->left;

    if (ptr->right != nullptr)
      free(ptr->right);
    delete ptr->right;
  }

  void insert(const int num)
  {
    Node *ptr = &root;
    for (int i = 31; i >= 0; i--)
    {
      bool bit = ((num >> i) & 1) == 0x1;

      if (bit)
      {
        if (ptr->left == nullptr)
          ptr->left = new Node;
        ptr = ptr->left;
      }
      else
      {
        if (ptr->right == nullptr)
          ptr->right = new Node;
        ptr = ptr->right;
      }
    }
  }

  int findMax(const int num)
  {
    Node *ptr = &root;
    int result = 0;
    for (int i = 31; i >= 0; i--)
    {
      if (ptr->right == nullptr and ptr->left == nullptr)
      {
        result <<= 1;
        continue;
      }

      bool bit = ((num >> i) & 1) == 0x1;

      if (bit)
      {
        if (ptr->right != nullptr)
        {
          ptr = ptr->right;
          result <<= 1;
        }
        else
        {
          ptr = ptr->left;
          result <<= 1;
          result += 1;
        }
      }
      else
      {
        if (ptr->left != nullptr)
        {
          ptr = ptr->left;
          result <<= 1;
          result += 1;
        }
        else
        {
          ptr = ptr->right;
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
