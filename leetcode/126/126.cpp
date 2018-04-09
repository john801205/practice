#include <cassert>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

class Solution
{
  public:
    std::vector<std::vector<std::string>>
    findLadders(const std::string beginWord,
                const std::string endWord,
                const std::vector<std::string>& wordList)
    {
      std::unordered_set<std::string> wordSet (std::begin(wordList), std::end(wordList));
      std::vector<std::vector<std::string>> results;

      if (wordSet.find(endWord) == wordSet.end())
      {
        return results;
      }

      std::unordered_map<std::string, std::vector<std::vector<std::string>>> steps;
      steps[beginWord] = {{beginWord}};
      steps[endWord] = {{endWord}};

      std::unordered_set<std::string> head ({beginWord});
      std::unordered_set<std::string> tail ({endWord});
      wordSet.erase(beginWord);
      wordSet.erase(endWord);

      while (!head.empty() && !tail.empty() && results.empty())
      {
        bool swapped = false;

        if (head.size() > tail.size())
        {
          swapped = true;
          std::swap(head, tail);
        }

        std::unordered_set<std::string> middle;

        for (auto word: head)
        {
          const auto orig = word;

          for (auto &ch: word)
          {
            const char temp = ch;

            for (char i = 'z'; i >= 'a'; i--)
            {
              ch = i;

              if (tail.find(word) != tail.end())
              {
                for (const auto &first: steps[orig])
                {
                  for (const auto &second: steps[word])
                  {
                    std::vector<std::string> step;
                    if (swapped)
                    {
                      step.insert(std::end(step), second.begin(), second.end());
                      step.insert(std::end(step), first.rbegin(), first.rend());
                    }
                    else
                    {
                      step.insert(std::end(step), first.begin(), first.end());
                      step.insert(std::end(step), second.rbegin(), second.rend());
                    }
                    results.emplace_back(step);
                  }
                }
              }

              if (wordSet.find(word) != wordSet.end())
              {
                std::vector<std::vector<std::string>> step = steps[orig];
                for (auto &s: step)
                {
                  s.emplace_back(word);
                }
                steps[word].insert(std::end(steps[word]), std::begin(step), std::end(step));

                middle.emplace(word);
              }
            }

            ch = temp;
          }
        }

        for (const auto &word: middle)
        {
          wordSet.erase(word);
        }

        std::swap(head, middle);

        if (swapped)
        {
          std::swap(head, tail);
        }
      }

      return results;
    }
};

int main(void)
{
  Solution s;
  assert(s.findLadders("hit", "cog", {"hot","dot","dog","lot","log","cog"}) == std::vector<std::vector<std::string>> ({{"hit","hot","dot","dog","cog"}, {"hit","hot","lot","log","cog"}}));
  return 0;
}
