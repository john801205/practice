#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>

bool cmp(const std::pair<int,int> &lhs, const std::pair<int,int> &rhs)
{
  if (lhs.first != rhs.first)
    return lhs.first > rhs.first;
  else
    return lhs.second < rhs.second;
}

class Solution
{
  public:
    std::vector<std::pair<int, int>>
    reconstructQueue(const std::vector<std::pair<int, int>> &people)
    {
      auto copy (people);
      std::sort(std::begin(copy), std::end(copy), cmp);

      std::vector<std::pair<int,int>> result;

      for (const auto &person: copy)
        result.insert(result.begin() + person.second, person);

      return result;
    }
};

int main()
{
  Solution s;
  assert(s.reconstructQueue({{7,0},{4,4},{7,1},{5,0},{6,1},{5,2}}) == (std::vector<std::pair<int,int>> ({{5,0},{7,0},{5,2},{6,1},{4,4},{7,1}})));
  return 0;
}
