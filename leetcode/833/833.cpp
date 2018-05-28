#include <cassert>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Replace
{
  std::string::size_type index;
  std::string source, target;

  Replace(std::string::size_type index, std::string source, std::string target):
    index(index), source(source), target(target)
  {
  }
};

bool operator<(const Replace &lft, const Replace &rht)
{
  return lft.index < rht.index;
}

class Solution
{
  public:
    std::string findReplaceString(const std::string              &S,
                                  const std::vector<int>         &indexes,
                                  const std::vector<std::string> &sources,
                                  const std::vector<std::string> &targets)
    {
      std::vector<Replace> replaces;
      for (std::vector<int>::size_type i = 0; i < indexes.size(); i++)
        replaces.emplace_back(indexes[i], sources[i], targets[i]);

      std::sort(std::begin(replaces), std::end(replaces));

      std::string result;
      std::vector<Replace>::size_type j = 0;

      for (std::string::size_type i = 0; i < S.size(); i++)
      {
        if (j < replaces.size() && replaces[j].index == i)
        {
          const std::string source = replaces[j].source;
          bool equal = true;

          for (std::string::size_type m = i, n = 0; equal && n < source.size(); m++, n++)
            if (S[m] != source[n])
              equal = false;

          if (equal)
          {
            result += replaces[j].target;
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
