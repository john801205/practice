#include <cassert>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution
{
  public:
    std::vector<std::vector<int>> palindromePairs(const std::vector<std::string> &words)
    {
      std::unordered_map<int, std::unordered_set<int>> result;
      std::unordered_map<std::string, int> maps;

      for (int i = 0; i < words.size(); i++)
      {
        maps[words[i]] = i;
      }

      for (int i = 0; i < words.size(); i++)
      {
        const std::string reversed (words[i].rbegin(), words[i].rend());
        std::string::size_type index = minReversedIndex(words[i]);
        std::string current = reversed.substr(0, index);

        if (maps.find(current) != maps.end() && maps[current] != i)
        {
          result[maps[current]].emplace(i);

          if (current == "")
            result[i].emplace(maps[current]);
        }

        while (index < reversed.size())
        {
          current += reversed[index];
          index++;

          if (maps.find(current) != maps.end()
              && maps[current] != i
              && isPalindrome(current + words[i]))
            result[maps[current]].emplace(i);
        }

        index = minReversedIndex(reversed);
        current = words[i].substr(0, index);

        std::string temp (current.rbegin(), current.rend());

        if (maps.find(temp) != maps.end() && maps[temp] != i)
        {
          result[i].emplace(maps[temp]);

          if (temp == "")
            result[maps[temp]].emplace(i);
        }

        while (index < words[i].size())
        {
          current += words[i][index];
          index++;

          std::string temp (current.rbegin(), current.rend());

          if (maps.find(temp) != maps.end()
              && maps[temp] != i
              && isPalindrome(words[i] + temp))
            result[i].emplace(maps[temp]);
        }
      }

      std::vector<std::vector<int>> results;
      for (const auto it: result)
      {
        for (const auto j: it.second)
        {
          results.push_back({it.first, j});
        }
      }

      return results;
    }

    bool isPalindrome(const std::string &word)
    {
      if (word.size() == 0)
        return true;

      std::string::size_type i = 0, j = word.size()-1;

      while (i < j)
      {
        if (word[i] != word[j])
          return false;

        i++;
        j--;
      }

      return true;
    }

    std::string::size_type minReversedIndex(const std::string &word)
    {
      const std::string reversed (word.rbegin(), word.rend());
      const auto nexts = makeNexts(word);

      std::string::size_type i, j;
      for (i = 0, j = 0; i < reversed.size(); )
      {
        if (reversed[i] == word[j])
        {
          i++;
          j++;
        }
        else
        {
          if (j == 0)
          {
            i++;
          }
          else
          {
            j = nexts[j-1];
          }
        }
      }

      return reversed.size() - j;
    }

    std::vector<std::string::size_type> makeNexts(const std::string &word)
    {
      std::vector<std::string::size_type> nexts (word.size(), 0);

      for (std::string::size_type i = 1, j = 0; i < word.size(); )
      {
        if (word[i] == word[j])
        {
          nexts[i] = j+1;
          i++;
          j++;
        }
        else
        {
          if (j == 0)
          {
            nexts[i] = 0;
            i++;
          }
          else
          {
            j = nexts[j-1];
          }
        }
      }

      return nexts;
    }
};

int main()
{
  Solution s;
  // assert(s.palindromePairs({"abcd","dcba","lls","s","sssll",""}) == std::vector<std::vector<int>> ({{0,1}, {1,0},{2,4},{3,2},{3,5},{5,3}}));
  // assert(s.palindromePairs({"abcd","dcba","lls","s","sssll"}) == std::vector<std::vector<int>> ({{0,1}, {1,0},{2,4},{3,2}}));

  // s.palindromePairs({"bbbbbabbabbbb","baabbaa","bbab","bbbabbaaab","abababbbbbab","abb","baaaabbb","babbaaaba","aab"});
  s.palindromePairs({"bbbbbabbabbbb","baabbaa","bbab","bbbabbaaab","abababbbbbab","abb","baaaabbb","babbaaaba","aab","aaaab","baabbbbabbaaaba","baaab","abbbab","abaabbbabbabba","aa","aabbbaabba","aaabbbbbaaabbbb","bbaaaaba","ababaaa","aaaaa","aaaaabbbbaaaba","abbabbbaabbaabbb","bbaba","aaaaabbbabbbbaaaab","abbbaa","bbbabbaaa","bbbaaabaabbbaaaaabaa","aaaabbabb","ababbababbbab","aaaaababaababbbabaaa","ba","bbbbababbbabab","baaaba","aababbaaabbb","aabbaaabbabaaababaab","abbbb","babaabaaababb","bbbbabaaaab","babbbbb","babaaba","aaba","abababba","a","bb","abaaab","babbabaababbabaaba","aaaaaababbbabaaabaa","baabaaabb","b","bbaaaabbb","abaaaaabaabbbaa","ab","bababaaaba","aabababb","ababaabbaababba","bbb","ababbaabababbbbbabb","bbbbb","abbbbaabaaaabb","baba","bbaabbabaaababaabbaa","bbaabaabbabbaab","bbbaabbab","babbbbbaaaaabaa","abbbbbbabbbabb","abaa","bbbbaababaab","abaaababa","aaaababaaababbaaba","bbabbbabbbbbbaab","abbabbabaabbabbbba","abbbbbaabbbaaabaaaa","bbaabababb","aaabababaabbaaaaaaab","ababbaabaaababb","abbbbabaaabbaaabbab","aababababbabaaa","baabbaabbbaaaaaa","bbbbbbbabbabbbbbb","bbbabbabbabbabaabba","babbbbabaaaabbabaab","baabaabaabababaaabba","bbaaaabbbbabbbaaaa","aaaaabaabaa","bbabaaabbbabaa","baaabaaaaaab","ababbbbbbbabaaaba","abbbabaababbbbbaaa","baaaaaabab","aabbabba","baaabbaabbbbaba","aaaaabba","babaaabbba","bbbbab","bbbbaabbaabab","baa","baababaa","abbbbb","babbaa","abbbabbaa"});
  return 0;
}
