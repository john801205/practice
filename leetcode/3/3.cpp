#include <algorithm>
#include <array>
#include <iostream>
#include <string>

class Solution
{
  public:
    int lengthOfLongestSubstring(std::string s)
    {
      int longest_length, start;
      std::array<int, 256> last_index;

      longest_length = 0;
      start = -1;
      std::fill(std::begin(last_index), std::end(last_index), -1);

      for (int i = 0; i < s.size(); i++)
      {
        if (last_index[s[i]] > start)
        {
          start = last_index[s[i]];
        }

        last_index[s[i]] = i;
        longest_length = std::max(longest_length, i - start);
      }

      return longest_length;
    }
};

int main(void)
{
  Solution s;
  std::cout << s.lengthOfLongestSubstring("abcabcbb") << '\n';
  return 0;
}
