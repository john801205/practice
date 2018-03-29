#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Solution
{
  public:
    std::vector<std::vector<std::string>>
    groupAnagrams(const std::vector<std::string> &strs)
    {
      std::unordered_map<std::string, std::vector<std::string>> maps;

      for (const auto &str: strs)
      {
        maps[strSort(str)].emplace_back(str);
      }

      std::vector<std::vector<std::string>> groups;
      for (const auto &map: maps)
      {
        groups.emplace_back(map.second);
      }

      return groups;
    }

  private:
    std::string strSort(const std::string &str)
    {
      int count[26] = {0};

      for (const auto &ch: str)
      {
        count[ch-'a']++;
      }

      std::string            result (str.size(), 'a');
      std::string::size_type p      = 0;

      for (int i = 0; i < 26; i++)
      {
        for (int j = 0; j < count[i]; j++)
        {
          result[p] += i;
          p++;
        }
      }

      return result;
    }
};

int main(void)
{
  Solution s;
  auto groups = s.groupAnagrams({"eat", "tea", "tan", "ate", "nat", "bat"});

  for (const auto &group: groups)
  {
    for (const auto &str: group)
    {
      std::cout << str << ' ';
    }
    std::cout << '\n';
  }

  return 0;
}
