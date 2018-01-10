#include <iostream>
#include <string>
#include <vector>

struct TrieNode
{
  unsigned index[2];
  bool isCode;

  TrieNode(void): index{0}, isCode{false} {}
};

int main(void)
{
  std::string code;
  int set_number = 1;

  while (std::cin >> code)
  {
    std::vector<TrieNode> Trie (1);
    bool is_prefix = false;

    do {
      if (code == "9")
        break;

      if (is_prefix)
        continue;

      unsigned index = 0;
      for (std::string::size_type i = 0; i < code.length(); i++)
      {
        const unsigned c = code[i] - '0';

        if (Trie[index].isCode)
        {
          is_prefix = true;
          break;
        }

        if (Trie[index].index[c] == 0)
        {
          Trie.emplace_back();
          Trie[index].index[c] = Trie.size() - 1;
        }

        index = Trie[index].index[c];
      }

      if (Trie[index].isCode
          || Trie[index].index[0] != 0
          || Trie[index].index[1] != 0)
        is_prefix = true;
      else
        Trie[index].isCode = true;

    } while (std::cin >> code);

    if (is_prefix)
      std::cout << "Set " << set_number << " is not immediately decodable\n";
    else
      std::cout << "Set " << set_number << " is immediately decodable\n";

    set_number++;
  }

  return 0;
}
