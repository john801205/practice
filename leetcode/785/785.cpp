#include <iostream>
#include <vector>
#include <stack>

enum Color
{
  none, black, white
};

class Solution
{
  public:
    bool isBipartite(std::vector<std::vector<int>>& graph)
    {
      std::vector<Color> colors (graph.size(), none);

      for (std::vector<std::vector<int>>::size_type i = 0; i < graph.size(); i++)
      {
        if (colors[i] == none)
        {
          colors[i] = black;

          if (!isBipartiteDFS(graph, i, colors))
          {
            return false;
          }
        }
      }

      return true;
    }

  private:
    bool isBipartiteDFS(const std::vector<std::vector<int>>            &graph,
                        const std::vector<std::vector<int>>::size_type  current,
                              std::vector<Color>                       &colors)
    {
      for (const auto &neighbor: graph[current])
      {
        if (colors[neighbor] == none)
        {
          colors[neighbor] = colors[current] == black ? white: black;

          if (!isBipartiteDFS(graph, neighbor, colors))
          {
            return false;
          }
        }
        else if (colors[neighbor] == colors[current])
        {
          return false;
        }
      }

      return true;
    }
};

int main(void)
{
  std::vector<std::vector<int>> graph = {{1,3},{0,2},{1,3},{0,2}};
  Solution s;
  std::cout << s.isBipartite(graph) << '\n';
  return 0;
}
