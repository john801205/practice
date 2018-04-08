#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Solution
{
  public:
    std::vector<int> findSubstring(const std::string &s,
                                   const std::vector<std::string> &words)
    {
      if (s.size() == 0 || words.size() == 0)
      {
        return {};
      }

      std::unordered_map<std::string, int> map;
      for (const auto &word: words)
      {
        map[word]++;
      }

      const std::string::size_type              wl    = words[0].size();
      const std::vector<std::string>::size_type total = words.size();
            std::vector<int>                    results;

      for (std::string::size_type i = 0; i < wl; i++)
      {
        std::string::size_type               left  = i;
        std::vector<std::string>::size_type  count = 0;
        std::unordered_map<std::string, int> window;

        for (std::string::size_type j = i; j + wl <= s.size(); j += wl)
        {
          std::string str = s.substr(j, wl);

          if (map.find(str) != map.end())
          {
            window[str]++;
            count++;

            while (window[str] > map[str])
            {
              std::string prev = s.substr(left, wl);
              window[prev]--;
              count--;
              left += wl;
            }

            if (count == total)
            {
              results.emplace_back(left);

              std::string prev = s.substr(left, wl);
              window[prev]--;
              count--;
              left += wl;
            }
          }
          else
          {
            window.clear();
            count = 0;
            left = j + wl;
          }
        }
      }

      return results;
    }
};

int main(void)
{
  Solution s;
  assert(s.findSubstring("", {"foo", "bar"}) == std::vector<int> ({}));
  assert(s.findSubstring("foobar", {}) == std::vector<int> ({}));
  assert(s.findSubstring("barfoothefoobarman", {"foo", "bar"}) == std::vector<int> ({0,9}));
  assert(s.findSubstring("barfoothebarman", {"foo", "bar", "the"}) == std::vector<int> ({0,3}));
  assert(s.findSubstring("foobarbooar", {"o", "o", "b"}) == std::vector<int> ({1,6}));
  assert(s.findSubstring("wordgoodgoodgoodbestword", {"word","good","best","good"}) == std::vector<int> ({8}));
  return 0;
}
