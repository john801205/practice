#include <cassert>
#include <stack>
#include <string>

class Solution
{
  public:
    std::string removeDuplicateLetters(const std::string &s)
    {
      int remainings[26] = {0};
      bool existed[26] = {false};

      for (const auto &ch: s)
        remainings[ch-'a']++;

      std::string result;
      for (const auto &ch: s)
      {
        remainings[ch-'a']--;
        if (existed[ch-'a'])
          continue;

        while (!result.empty()
            && ch < result.back()
            && remainings[result.back()-'a'] != 0)
        {
          existed[result.back()-'a'] = false;
          result.pop_back();
        }

        result.push_back(ch);
        existed[ch-'a'] = true;
      }

      return result;
    }
};

int main(void)
{
  Solution s;
  assert(s.removeDuplicateLetters("bcabc") == "abc");
  assert(s.removeDuplicateLetters("cbacdcbc") == "acdb");
  return 0;
}
