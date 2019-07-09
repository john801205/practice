#include <string>

class Solution
{
  public:
    std::string reverseWords(std::string s)
    {
      for (std::string::size_type i = 0; i < s.size(); i++)
      {
        if (s[i] == ' ')
          continue;

        std::string::size_type start = i, end = i;
        while (end+1 < s.size() && s[end+1] != ' ')
          end++;
        i = end;

        while (start < end)
        {
          std::swap(s[start], s[end]);
          start++;
          end--;
        }
      }

      return s;
    }
};

int main()
{
  return 0;
}
