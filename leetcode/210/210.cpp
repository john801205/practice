#include <iostream>
#include <queue>
#include <utility>
#include <unordered_set>
#include <vector>

class Solution
{
  public:
    std::vector<int> findOrder(int numCourses, std::vector<std::pair<int, int>>& prerequisites)
    {
      std::vector<std::unordered_set<int>> graph(numCourses);
      std::vector<std::unordered_set<int>> reverse(numCourses);

      for (const auto &prerequisite: prerequisites)
      {
        graph[prerequisite.first].insert(prerequisite.second);
        reverse[prerequisite.second].insert(prerequisite.first);
      }

      std::vector<int> result;
      std::queue<int> zero_degree;

      for (std::vector<std::unordered_set<int>>::size_type i = 0; i < graph.size(); i++)
      {
        if (graph[i].size() == 0)
        {
          zero_degree.push(i);
        }
      }

      while (!zero_degree.empty())
      {
        const int i = zero_degree.front();

        zero_degree.pop();
        result.push_back(i);

        for (const auto &neighbor: reverse[i])
        {
          graph[neighbor].erase(i);

          if (graph[neighbor].size() == 0)
          {
            zero_degree.push(neighbor);
          }
        }
      }

      if (result.size() != graph.size())
      {
        return {};
      }
      else
      {
        return result;
      }
    }
};

int main(void)
{
  std::vector<std::pair<int, int>> prerequisites;
  prerequisites.push_back(std::make_pair(1, 0));
  prerequisites.push_back(std::make_pair(2, 0));
  prerequisites.push_back(std::make_pair(3, 1));
  prerequisites.push_back(std::make_pair(3, 2));

  Solution s;

  for (const auto &v: s.findOrder(4, prerequisites))
    std::cerr << v << ' ';
  std::cerr << '\n';

  return 0;
}
