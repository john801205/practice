#include <cassert>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Solution
{
  public:
    std::string findReplaceString(const std::string              &S,
                                  const std::vector<int>         &indexes,
                                  const std::vector<std::string> &sources,
                                  const std::vector<std::string> &targets)
    {
      std::vector<std::pair<std::vector<int>::size_type, std::vector<int>::size_type>> sorted;
      for (std::vector<int>::size_type i = 0; i < indexes.size(); i++)
        sorted.emplace_back(indexes[i], i);

      std::sort(std::begin(sorted), std::end(sorted));

      std::string result;
      std::vector<int>::size_type j = 0;

      for (std::string::size_type i = 0; i < S.size(); i++)
      {
        if (j < sorted.size() && sorted[j].first == i)
        {
          const std::string source = sources[sorted[j].second];
          bool equal = true;

          for (std::string::size_type m = i, n = 0; equal && n < source.size(); m++, n++)
            if (S[m] != source[n])
              equal = false;

          if (equal)
          {
            result += targets[sorted[j].second];
            i += source.size()-1;
          }
          else
          {
            result += S[i];
          }

          j++;
        }
        else
        {
          result += S[i];
        }
      }

      return result;
    }
};

int main()
{
  Solution s;
  assert(s.findReplaceString("abcd", {0,2}, {"a", "cd"}, {"eee", "ffff"}) == "eeebffff");
  return 0;
}
