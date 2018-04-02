#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

class Solution
{
  public:
    std::vector<std::string> wordBreak(const std::string s, const std::vector<std::string>& wordDict)
    {
      std::unordered_map<std::string, std::vector<std::string>> cache;
      std::unordered_set<std::string> set (std::begin(wordDict), std::end(wordDict));
      return backtracking(s, set, cache);
    }

    std::vector<std::string> backtracking(const std::string s,
                                          const std::unordered_set<std::string> &set,
                                                std::unordered_map<std::string, std::vector<std::string>> &cache)
    {
      auto search = cache.find(s);
      if (search != cache.end())
      {
        return search->second;
      }

      std::vector<std::string> result;

      for (std::string::size_type i = s.size(); i-- > 1; )
      {
        std::string word = s.substr(i);

        if (set.find(word) != set.end())
        {
          auto prefixes = backtracking(s.substr(0, i), set, cache);
          for (const auto &prefix: prefixes)
          {
            result.emplace_back(prefix + ' ' + word);
          }
        }
      }

      if (set.find(s) != set.end())
      {
        result.emplace_back(s);
      }

      cache[s] = result;
      return result;
    }
};

int main(void)
{
  Solution s;
  assert(s.wordBreak("catsanddog", {"cat", "cats", "and", "sand", "dog"}) == std::vector<std::string> ({"cats and dog","cat sand dog"}));
  assert(s.wordBreak("catsanddog", {}) == std::vector<std::string> ());
  assert(s.wordBreak("catsanddog", {"cats"}) == std::vector<std::string> ());
  assert(s.wordBreak("catsanddogee", {"cat", "cats", "and", "sand", "dog", "e", "ee"}) == std::vector<std::string> ({"cats and dog e e","cat sand dog e e","cats and dog ee","cat sand dog ee"}));
  assert(s.wordBreak("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"}) == std::vector<std::string> ());
  assert(s.wordBreak("aaaaaaaaaa", {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"}) == std::vector<std::string> ({"a a a a a a a a a a","aa a a a a a a a a","a aa a a a a a a a","aaa a a a a a a a","a a aa a a a a a a","aa aa a a a a a a","a aaa a a a a a a","aaaa a a a a a a","a a a aa a a a a a","aa a aa a a a a a","a aa aa a a a a a","aaa aa a a a a a","a a aaa a a a a a","aa aaa a a a a a","a aaaa a a a a a","aaaaa a a a a a","a a a a aa a a a a","aa a a aa a a a a","a aa a aa a a a a","aaa a aa a a a a","a a aa aa a a a a","aa aa aa a a a a","a aaa aa a a a a","aaaa aa a a a a","a a a aaa a a a a","aa a aaa a a a a","a aa aaa a a a a","aaa aaa a a a a","a a aaaa a a a a","aa aaaa a a a a","a aaaaa a a a a","aaaaaa a a a a","a a a a a aa a a a","aa a a a aa a a a","a aa a a aa a a a","aaa a a aa a a a","a a aa a aa a a a","aa aa a aa a a a","a aaa a aa a a a","aaaa a aa a a a","a a a aa aa a a a","aa a aa aa a a a","a aa aa aa a a a","aaa aa aa a a a","a a aaa aa a a a","aa aaa aa a a a","a aaaa aa a a a","aaaaa aa a a a","a a a a aaa a a a","aa a a aaa a a a","a aa a aaa a a a","aaa a aaa a a a","a a aa aaa a a a","aa aa aaa a a a","a aaa aaa a a a","aaaa aaa a a a","a a a aaaa a a a","aa a aaaa a a a","a aa aaaa a a a","aaa aaaa a a a","a a aaaaa a a a","aa aaaaa a a a","a aaaaaa a a a","aaaaaaa a a a","a a a a a a aa a a","aa a a a a aa a a","a aa a a a aa a a","aaa a a a aa a a","a a aa a a aa a a","aa aa a a aa a a","a aaa a a aa a a","aaaa a a aa a a","a a a aa a aa a a","aa a aa a aa a a","a aa aa a aa a a","aaa aa a aa a a","a a aaa a aa a a","aa aaa a aa a a","a aaaa a aa a a","aaaaa a aa a a","a a a a aa aa a a","aa a a aa aa a a","a aa a aa aa a a","aaa a aa aa a a","a a aa aa aa a a","aa aa aa aa a a","a aaa aa aa a a","aaaa aa aa a a","a a a aaa aa a a","aa a aaa aa a a","a aa aaa aa a a","aaa aaa aa a a","a a aaaa aa a a","aa aaaa aa a a","a aaaaa aa a a","aaaaaa aa a a","a a a a a aaa a a","aa a a a aaa a a","a aa a a aaa a a","aaa a a aaa a a","a a aa a aaa a a","aa aa a aaa a a","a aaa a aaa a a","aaaa a aaa a a","a a a aa aaa a a","aa a aa aaa a a","a aa aa aaa a a","aaa aa aaa a a","a a aaa aaa a a","aa aaa aaa a a","a aaaa aaa a a","aaaaa aaa a a","a a a a aaaa a a","aa a a aaaa a a","a aa a aaaa a a","aaa a aaaa a a","a a aa aaaa a a","aa aa aaaa a a","a aaa aaaa a a","aaaa aaaa a a","a a a aaaaa a a","aa a aaaaa a a","a aa aaaaa a a","aaa aaaaa a a","a a aaaaaa a a","aa aaaaaa a a","a aaaaaaa a a","aaaaaaaa a a","a a a a a a a aa a","aa a a a a a aa a","a aa a a a a aa a","aaa a a a a aa a","a a aa a a a aa a","aa aa a a a aa a","a aaa a a a aa a","aaaa a a a aa a","a a a aa a a aa a","aa a aa a a aa a","a aa aa a a aa a","aaa aa a a aa a","a a aaa a a aa a","aa aaa a a aa a","a aaaa a a aa a","aaaaa a a aa a","a a a a aa a aa a","aa a a aa a aa a","a aa a aa a aa a","aaa a aa a aa a","a a aa aa a aa a","aa aa aa a aa a","a aaa aa a aa a","aaaa aa a aa a","a a a aaa a aa a","aa a aaa a aa a","a aa aaa a aa a","aaa aaa a aa a","a a aaaa a aa a","aa aaaa a aa a","a aaaaa a aa a","aaaaaa a aa a","a a a a a aa aa a","aa a a a aa aa a","a aa a a aa aa a","aaa a a aa aa a","a a aa a aa aa a","aa aa a aa aa a","a aaa a aa aa a","aaaa a aa aa a","a a a aa aa aa a","aa a aa aa aa a","a aa aa aa aa a","aaa aa aa aa a","a a aaa aa aa a","aa aaa aa aa a","a aaaa aa aa a","aaaaa aa aa a","a a a a aaa aa a","aa a a aaa aa a","a aa a aaa aa a","aaa a aaa aa a","a a aa aaa aa a","aa aa aaa aa a","a aaa aaa aa a","aaaa aaa aa a","a a a aaaa aa a","aa a aaaa aa a","a aa aaaa aa a","aaa aaaa aa a","a a aaaaa aa a","aa aaaaa aa a","a aaaaaa aa a","aaaaaaa aa a","a a a a a a aaa a","aa a a a a aaa a","a aa a a a aaa a","aaa a a a aaa a","a a aa a a aaa a","aa aa a a aaa a","a aaa a a aaa a","aaaa a a aaa a","a a a aa a aaa a","aa a aa a aaa a","a aa aa a aaa a","aaa aa a aaa a","a a aaa a aaa a","aa aaa a aaa a","a aaaa a aaa a","aaaaa a aaa a","a a a a aa aaa a","aa a a aa aaa a","a aa a aa aaa a","aaa a aa aaa a","a a aa aa aaa a","aa aa aa aaa a","a aaa aa aaa a","aaaa aa aaa a","a a a aaa aaa a","aa a aaa aaa a","a aa aaa aaa a","aaa aaa aaa a","a a aaaa aaa a","aa aaaa aaa a","a aaaaa aaa a","aaaaaa aaa a","a a a a a aaaa a","aa a a a aaaa a","a aa a a aaaa a","aaa a a aaaa a","a a aa a aaaa a","aa aa a aaaa a","a aaa a aaaa a","aaaa a aaaa a","a a a aa aaaa a","aa a aa aaaa a","a aa aa aaaa a","aaa aa aaaa a","a a aaa aaaa a","aa aaa aaaa a","a aaaa aaaa a","aaaaa aaaa a","a a a a aaaaa a","aa a a aaaaa a","a aa a aaaaa a","aaa a aaaaa a","a a aa aaaaa a","aa aa aaaaa a","a aaa aaaaa a","aaaa aaaaa a","a a a aaaaaa a","aa a aaaaaa a","a aa aaaaaa a","aaa aaaaaa a","a a aaaaaaa a","aa aaaaaaa a","a aaaaaaaa a","aaaaaaaaa a","a a a a a a a a aa","aa a a a a a a aa","a aa a a a a a aa","aaa a a a a a aa","a a aa a a a a aa","aa aa a a a a aa","a aaa a a a a aa","aaaa a a a a aa","a a a aa a a a aa","aa a aa a a a aa","a aa aa a a a aa","aaa aa a a a aa","a a aaa a a a aa","aa aaa a a a aa","a aaaa a a a aa","aaaaa a a a aa","a a a a aa a a aa","aa a a aa a a aa","a aa a aa a a aa","aaa a aa a a aa","a a aa aa a a aa","aa aa aa a a aa","a aaa aa a a aa","aaaa aa a a aa","a a a aaa a a aa","aa a aaa a a aa","a aa aaa a a aa","aaa aaa a a aa","a a aaaa a a aa","aa aaaa a a aa","a aaaaa a a aa","aaaaaa a a aa","a a a a a aa a aa","aa a a a aa a aa","a aa a a aa a aa","aaa a a aa a aa","a a aa a aa a aa","aa aa a aa a aa","a aaa a aa a aa","aaaa a aa a aa","a a a aa aa a aa","aa a aa aa a aa","a aa aa aa a aa","aaa aa aa a aa","a a aaa aa a aa","aa aaa aa a aa","a aaaa aa a aa","aaaaa aa a aa","a a a a aaa a aa","aa a a aaa a aa","a aa a aaa a aa","aaa a aaa a aa","a a aa aaa a aa","aa aa aaa a aa","a aaa aaa a aa","aaaa aaa a aa","a a a aaaa a aa","aa a aaaa a aa","a aa aaaa a aa","aaa aaaa a aa","a a aaaaa a aa","aa aaaaa a aa","a aaaaaa a aa","aaaaaaa a aa","a a a a a a aa aa","aa a a a a aa aa","a aa a a a aa aa","aaa a a a aa aa","a a aa a a aa aa","aa aa a a aa aa","a aaa a a aa aa","aaaa a a aa aa","a a a aa a aa aa","aa a aa a aa aa","a aa aa a aa aa","aaa aa a aa aa","a a aaa a aa aa","aa aaa a aa aa","a aaaa a aa aa","aaaaa a aa aa","a a a a aa aa aa","aa a a aa aa aa","a aa a aa aa aa","aaa a aa aa aa","a a aa aa aa aa","aa aa aa aa aa","a aaa aa aa aa","aaaa aa aa aa","a a a aaa aa aa","aa a aaa aa aa","a aa aaa aa aa","aaa aaa aa aa","a a aaaa aa aa","aa aaaa aa aa","a aaaaa aa aa","aaaaaa aa aa","a a a a a aaa aa","aa a a a aaa aa","a aa a a aaa aa","aaa a a aaa aa","a a aa a aaa aa","aa aa a aaa aa","a aaa a aaa aa","aaaa a aaa aa","a a a aa aaa aa","aa a aa aaa aa","a aa aa aaa aa","aaa aa aaa aa","a a aaa aaa aa","aa aaa aaa aa","a aaaa aaa aa","aaaaa aaa aa","a a a a aaaa aa","aa a a aaaa aa","a aa a aaaa aa","aaa a aaaa aa","a a aa aaaa aa","aa aa aaaa aa","a aaa aaaa aa","aaaa aaaa aa","a a a aaaaa aa","aa a aaaaa aa","a aa aaaaa aa","aaa aaaaa aa","a a aaaaaa aa","aa aaaaaa aa","a aaaaaaa aa","aaaaaaaa aa","a a a a a a a aaa","aa a a a a a aaa","a aa a a a a aaa","aaa a a a a aaa","a a aa a a a aaa","aa aa a a a aaa","a aaa a a a aaa","aaaa a a a aaa","a a a aa a a aaa","aa a aa a a aaa","a aa aa a a aaa","aaa aa a a aaa","a a aaa a a aaa","aa aaa a a aaa","a aaaa a a aaa","aaaaa a a aaa","a a a a aa a aaa","aa a a aa a aaa","a aa a aa a aaa","aaa a aa a aaa","a a aa aa a aaa","aa aa aa a aaa","a aaa aa a aaa","aaaa aa a aaa","a a a aaa a aaa","aa a aaa a aaa","a aa aaa a aaa","aaa aaa a aaa","a a aaaa a aaa","aa aaaa a aaa","a aaaaa a aaa","aaaaaa a aaa","a a a a a aa aaa","aa a a a aa aaa","a aa a a aa aaa","aaa a a aa aaa","a a aa a aa aaa","aa aa a aa aaa","a aaa a aa aaa","aaaa a aa aaa","a a a aa aa aaa","aa a aa aa aaa","a aa aa aa aaa","aaa aa aa aaa","a a aaa aa aaa","aa aaa aa aaa","a aaaa aa aaa","aaaaa aa aaa","a a a a aaa aaa","aa a a aaa aaa","a aa a aaa aaa","aaa a aaa aaa","a a aa aaa aaa","aa aa aaa aaa","a aaa aaa aaa","aaaa aaa aaa","a a a aaaa aaa","aa a aaaa aaa","a aa aaaa aaa","aaa aaaa aaa","a a aaaaa aaa","aa aaaaa aaa","a aaaaaa aaa","aaaaaaa aaa","a a a a a a aaaa","aa a a a a aaaa","a aa a a a aaaa","aaa a a a aaaa","a a aa a a aaaa","aa aa a a aaaa","a aaa a a aaaa","aaaa a a aaaa","a a a aa a aaaa","aa a aa a aaaa","a aa aa a aaaa","aaa aa a aaaa","a a aaa a aaaa","aa aaa a aaaa","a aaaa a aaaa","aaaaa a aaaa","a a a a aa aaaa","aa a a aa aaaa","a aa a aa aaaa","aaa a aa aaaa","a a aa aa aaaa","aa aa aa aaaa","a aaa aa aaaa","aaaa aa aaaa","a a a aaa aaaa","aa a aaa aaaa","a aa aaa aaaa","aaa aaa aaaa","a a aaaa aaaa","aa aaaa aaaa","a aaaaa aaaa","aaaaaa aaaa","a a a a a aaaaa","aa a a a aaaaa","a aa a a aaaaa","aaa a a aaaaa","a a aa a aaaaa","aa aa a aaaaa","a aaa a aaaaa","aaaa a aaaaa","a a a aa aaaaa","aa a aa aaaaa","a aa aa aaaaa","aaa aa aaaaa","a a aaa aaaaa","aa aaa aaaaa","a aaaa aaaaa","aaaaa aaaaa","a a a a aaaaaa","aa a a aaaaaa","a aa a aaaaaa","aaa a aaaaaa","a a aa aaaaaa","aa aa aaaaaa","a aaa aaaaaa","aaaa aaaaaa","a a a aaaaaaa","aa a aaaaaaa","a aa aaaaaaa","aaa aaaaaaa","a a aaaaaaaa","aa aaaaaaaa","a aaaaaaaaa","aaaaaaaaaa"}));
  return 0;
}
