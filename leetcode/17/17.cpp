#include <cassert>

#include <iostream>
#include <string>
#include <vector>

class Solution
{
  public:
    std::vector<std::string> letterCombinations(const std::string digits)
    {
      static const std::vector<std::vector<std::string>> maps = {{}, {}, {"a", "b", "c"}, {"d", "e", "f"}, {"g", "h", "i"}, {"j", "k", "l"}, {"m", "n", "o"}, {"p", "q", "r", "s"}, {"t", "u", "v"}, {"w", "x", "y", "z"}};

      if (digits.size() == 0)
      {
        return {};
      }

      if (digits.size() == 1)
      {
        return maps[digits[0] - '0'];
      }

      std::vector<std::string> results;
      std::vector<std::string> combs = letterCombinations(digits.substr(1));

      for (const auto &string: maps[digits[0] - '0'])
      {
        for (const auto &comb: combs)
        {
          results.emplace_back(string + comb);
        }
      }

      return results;
    }
};

int main(void)
{
  Solution s;
  assert(s.letterCombinations("23") == std::vector<std::string> ({"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"}));
  assert(s.letterCombinations("456") == std::vector<std::string> ({"gjm","gjn","gjo","gkm","gkn","gko","glm","gln","glo","hjm","hjn","hjo","hkm","hkn","hko","hlm","hln","hlo","ijm","ijn","ijo","ikm","ikn","iko","ilm","iln","ilo"}));
  assert(s.letterCombinations("789") == std::vector<std::string> ({"ptw","ptx","pty","ptz","puw","pux","puy","puz","pvw","pvx","pvy","pvz","qtw","qtx","qty","qtz","quw","qux","quy","quz","qvw","qvx","qvy","qvz","rtw","rtx","rty","rtz","ruw","rux","ruy","ruz","rvw","rvx","rvy","rvz","stw","stx","sty","stz","suw","sux","suy","suz","svw","svx","svy","svz"}));

  assert(s.letterCombinations("123") == std::vector<std::string> ());
  assert(s.letterCombinations("230") == std::vector<std::string> ());

  assert(s.letterCombinations("") == std::vector<std::string> ());


  return 0;
}
