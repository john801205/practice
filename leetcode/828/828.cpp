#include <cassert>
#include <iostream>
#include <string>

class Solution
{
  public:
    int uniqueLetterString(const std::string S)
    {
      int total = 0;
      int last[26], last2[26];

      for (int i = 0; i < 26; i++)
      {
        last[i] = -1;
        last2[i] = -1;
      }

      for (std::string::size_type i = 0; i < S.size(); i++)
      {
        const int s = S[i] - 'A';
        total = (total + (i - last[s]) * (last[s] - last2[s]) % 1000000007) % 10000007;
        last2[s] = last[s];
        last[s] = i;
      }

      for (int i = 0; i < 26; i++)
      {
        total = (total + (S.size() - last[i]) * (last[i] - last2[i]) % 1000000007) % 10000007;
      }

      return total;
    }
};

int main()
{
  Solution s;
  assert(s.uniqueLetterString("ABC") == 10);
  assert(s.uniqueLetterString("ABA") == 8);
  assert(s.uniqueLetterString("ABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABC") == 1386);
  return 0;
}
