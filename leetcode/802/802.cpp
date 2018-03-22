#include <iostream>
#include <vector>

enum color
{
  white, gray, black
};

class Solution
{
  public:
    std::vector<int> eventualSafeNodes(std::vector<std::vector<int>>& graph)
    {
      std::vector<int>  result;
      std::vector<bool> circles (graph.size(), false);
      std::vector<color> visited (graph.size(), white);

      for (std::vector<std::vector<int>>::size_type i = 0; i < graph.size(); i++)
      {
        if (visited[i] == white)
        {
          dfs(graph, i, visited, circles);
        }
      }

      for (std::vector<bool>::size_type i = 0; i < circles.size(); i++)
      {
        if (!circles[i])
        {
          result.push_back(i);
        }
      }

      return result;
    }

  private:
    void dfs(const std::vector<std::vector<int>>            &graph,
             const std::vector<std::vector<int>>::size_type  i,
                   std::vector<color>                       &visited,
                   std::vector<bool>                        &circles)
    {
      visited[i] = gray;

      for (const auto &neighbor: graph[i])
      {
        if (visited[neighbor] == gray)
        {
          circles[i] = true;
        }
        else if (visited[neighbor] == black)
        {
          circles[i] = circles[neighbor];
        }
        else
        {
          dfs(graph, neighbor, visited, circles);
          circles[i] = circles[neighbor];
        }

        if (circles[i])
        {
          break;
        }
      }

      visited[i] = black;
    }
};

int main(void)
{
  std::vector<std::vector<int>> graph = {{1, 2}, {2, 3}, {5}, {0}, {5}, {}, {}};
  Solution s;
  std::vector<int> r = s.eventualSafeNodes(graph);

  for (const auto &v: r)
    std::cout << v << ' ';
  std::cout << '\n';

  return 0;
}
