#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

class WordFilter
{
  private:
    std::vector<std::array<std::vector<char>::size_type, 26>> prefix;
    std::vector<std::array<std::vector<char>::size_type, 26>> suffix;

    std::vector<std::vector<std::vector<char>::size_type>> prefix_weights;
    std::vector<std::vector<std::vector<char>::size_type>> suffix_weights;

    void addtoTrie(std::vector<std::array<std::vector<char>::size_type, 26>> &trie,
                   std::vector<std::vector<std::string::size_type>>          &trie_weights,
                   const std::string::size_type                               weight,
                   const std::string                                          word)
    {
      std::vector<char>::size_type current = 0;
      trie_weights[current].emplace_back(weight);

      for (const auto c: word)
      {
        if (trie[current][c-'a'] == 0)
        {
          trie[current][c-'a'] = trie.size();
          trie.push_back({0});
          trie_weights.emplace_back();
        }

        current = trie[current][c-'a'];
        trie_weights[current].emplace_back(weight);
      }
    }

    std::vector<std::string::size_type>
    lookupTrie(std::vector<std::array<std::vector<char>::size_type, 26>> &trie,
               std::vector<std::vector<std::string::size_type>>          &trie_weights,
               const std::string                                          word)
    {
      std::vector<char>::size_type current = 0;

      for (const auto c: word)
      {
        if (trie[current][c-'a'] == 0)
          return {};

        current = trie[current][c-'a'];
      }

      return trie_weights[current];
    }

  public:
    WordFilter(const std::vector<std::string> &words):
      prefix(1, {0}), suffix(1, {0}), prefix_weights(1), suffix_weights(1)
    {
      for (std::vector<std::string>::size_type i = 0; i < words.size(); i++)
      {
        addtoTrie(prefix, prefix_weights, i, words[i]);

        std::string rev = words[i];
        std::reverse(std::begin(rev), std::end(rev));

        addtoTrie(suffix, suffix_weights, i, rev);
      }
    }

    int f(const std::string prefix, const std::string suffix)
    {
      auto weight1 = lookupTrie(this->prefix, prefix_weights, prefix);
      if (weight1.size() == 0)
        return -1;

      std::string rev = suffix;
      std::reverse(std::begin(rev), std::end(rev));
      auto weight2 = lookupTrie(this->suffix, suffix_weights, rev);
      if (weight2.size() == 0)
        return -1;

      for (auto i = weight1.rbegin(), j = weight2.rbegin(); i < weight1.rend() && j < weight2.rend();)
      {
        if (*i == *j)
          return *i;
        else if (*i > *j)
          i++;
        else
          j++;
      }

      return -1;
    }
};

int main()
{
  /**
   * Your WordFilter object will be instantiated and called as such:
   * WordFilter obj = new WordFilter(words);
   * int param_1 = obj.f(prefix,suffix);
   */

  WordFilter obj ({"apple", "appple", "bcdef", "ae"});
  std::cout << obj.f("a", "le") << '\n';
  std::cout << obj.f("bc", "ef") << '\n';
  std::cout << obj.f("c", "") << '\n';

  return 0;
}
