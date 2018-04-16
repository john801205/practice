#include <cassert>
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

class Trie
{
  private:
    std::vector<std::array<int, 26>> tree;

  public:
    Trie(): tree(1, std::array<int, 26> {}) {}

    void add(const std::string &str)
    {
      std::vector<std::array<int, 26>>::size_type pos = 0;

      for (const auto &c: str)
      {
        if (tree[pos][c-'a'] == 0)
        {
          tree[pos][c-'a'] = tree.size();
          tree.emplace_back(std::array<int, 26> {});
        }

        pos = tree[pos][c-'a'];
      }
    }

    bool exist(const std::string &str) const
    {
      std::vector<std::array<int, 26>>::size_type pos = 0;

      for (const auto &c: str)
      {
        if (tree[pos][c-'a'] == 0)
          return false;

        pos = tree[pos][c-'a'];
      }

      return true;
    }
};

class Solution
{
  public:
    std::vector<std::string>
    findWords(const std::vector<std::vector<char>> &board,
              const std::vector<std::string>       &words)
    {
      std::vector<std::string> results;
      std::unordered_set<std::string> sets, duplicates;
      Trie trie;

      sets.insert(words.begin(), words.end());

      for (const auto &word: words)
        trie.add(word);

      for (std::vector<char>::size_type i = 0; i < board.size(); i++)
      {
        for (std::vector<char>::size_type j = 0; j < board[i].size(); j++)
        {
          std::vector<std::vector<bool>> visited (board.size(), std::vector<bool> (board[0].size(), false));
          std::string stack;

          dfs(board, i, j, trie, sets, duplicates, visited, stack, results);
        }
      }

      std::sort(results.begin(), results.end());
      return results;
    }

    void dfs(const std::vector<std::vector<char>>  &board,
             const std::vector<char>::size_type     row,
             const std::vector<char>::size_type     col,
             const Trie                            &trie,
             const std::unordered_set<std::string> &sets,
                   std::unordered_set<std::string> &duplicates,
                   std::vector<std::vector<bool>>  &visited,
                   std::string                     &stack,
                   std::vector<std::string>        &results)
    {
      if (!trie.exist(stack) || visited[row][col])
        return;

      stack.push_back(board[row][col]);
      visited[row][col] = true;

      if (sets.find(stack) != sets.end() && duplicates.find(stack) == duplicates.end())
      {
        results.emplace_back(stack);
        duplicates.emplace(stack);
      }

      std::vector<std::vector<int>> dirs ({{-1, 0}, {1, 0}, {0, -1}, {0, 1}});

      for (const auto &dir: dirs)
      {
        auto i = row + dir[0], j = col + dir[1];

        if (i >= board.size() || j >= board[i].size())
          continue;

        dfs(board, i, j, trie, sets, duplicates, visited, stack, results);
      }

      stack.pop_back();
      visited[row][col] = false;
    }
};

int main(void)
{
  Trie trie;
  trie.add("aabcd");
  assert(!trie.exist("c"));
  assert(trie.exist("aabc"));
  assert(trie.exist("aabcd"));
  assert(!trie.exist("aabcde"));

  Solution s;
  s.findWords({{'a'}}, {"a"});
  return 0;
}
