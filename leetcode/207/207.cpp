#include <iostream>
#include <utility>
#include <unordered_set>
#include <vector>

class Solution
{
  public:
    bool DFS(const int                                   course,
             const std::vector<std::unordered_set<int>> &graph,
                   std::unordered_set<int>              &prerequisites,
                   std::vector<bool>                    &visited)
    {
      if (prerequisites.count(course) > 0)
        return false;

      prerequisites.insert(course);
      visited[course] = true;

      for (const auto prerequisite: graph[course])
      {
        if (!DFS(prerequisite, graph, prerequisites, visited))
        {
          return false;
        }
      }

      prerequisites.erase(course);
      return true;
    }

    bool canFinish(int numCourses, std::vector<std::pair<int, int>>& prerequisites)
    {
      std::vector<std::unordered_set<int>> graph (numCourses);
      std::vector<bool> visited (numCourses, false);

      for (const auto &req: prerequisites)
      {
        graph[req.first].insert(req.second);
      }

      for (int i = 0; i < numCourses; i++)
      {
        std::unordered_set<int> stack;
        if (!visited[i] && !DFS(i, graph, stack, visited))
        {
          return false;
        }
      }

      return true;
    }
};

int main(void)
{
  std::vector<std::pair<int, int>> prerequisites;
  prerequisites.push_back(std::make_pair(0, 1));
  prerequisites.push_back(std::make_pair(0, 2));
  prerequisites.push_back(std::make_pair(1, 2));

  Solution s;
  std::cerr << s.canFinish(3, prerequisites) << '\n';

  return 0;
}
