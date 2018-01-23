#include <algorithm>
#include <functional>
#include <iostream>
#include <stack>
#include <vector>

struct Edge
{
  unsigned x, y, weight;

  Edge(unsigned x, unsigned y, unsigned weight): x(x),
                                                 y(y),
                                                 weight(weight) {}

  friend bool operator< (const Edge &lhs, const Edge &rhs)
  {
    return lhs.weight < rhs.weight;
  }
};

int main(void)
{
  unsigned number_of_nodes, number_of_edges;

  while (std::cin >> number_of_nodes >> number_of_edges)
  {
    if (number_of_nodes == 0 and number_of_edges == 0)
      break;

    // degree[i] stores the degree of node i
    std::vector<Edge> edges;
    // parent[i] stores the parent of node i
    std::vector<int> parent(number_of_nodes, -1);
    // heavy_cycle_edges stores the result
    std::vector<unsigned> heavy_cycle_edges;

    for (unsigned i = 0; i < number_of_edges; i++)
    {
      unsigned x, y, weight;
      std::cin >> x >> y >> weight;

      edges.emplace_back(x, y, weight);
    }

    // sort the edges in the increasing weight order
    std::sort(std::begin(edges), std::end(edges));

    for (auto &edge: edges)
    {
      // find parent of x
      unsigned parent_x = edge.x;
      while (parent[parent_x] != -1)
        parent_x = parent[parent_x];

      // change the parent of internal to parent_x
      for (unsigned i = edge.x; parent[i] != -1; )
      {
        unsigned temp = parent[i];
        parent[i] = parent_x;
        i = temp;
      }

      // find parent of y
      unsigned parent_y = edge.y;
      while (parent[parent_y] != -1)
        parent_y = parent[parent_y];

      // change the parent of internal to parent_y
      for (int i = edge.y; parent[i] != -1; )
      {
        unsigned temp = parent[i];
        parent[i] = parent_y;
        i = temp;
      }

      // if they are connected
      if (parent_x == parent_y)
        heavy_cycle_edges.push_back(edge.weight);
      else
        parent[parent_x] = parent_y;
    }

    if (!heavy_cycle_edges.empty())
    {
      std::cout << heavy_cycle_edges[0];
      for (std::vector<unsigned>::size_type i = 1;
           i < heavy_cycle_edges.size();
           i++)
        std::cout << ' ' << heavy_cycle_edges[i];

      std::cout << '\n';
    }
    else
    {
      std::cout << "forest\n";
    }
  }

  return 0;
}
