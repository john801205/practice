#include <climits>

#include <algorithm>
#include <iostream>
#include <vector>

struct Node
{
  int id, parent, key;

  Node(int id, int parent, int key): id(id), parent(parent), key(key) {}

  Node(const Node &x): id(x.id), parent(x.parent), key(x.key) {}
};

struct Edge
{
  int x, y, length;

  Edge(int x, int y, int length): x(x), y(y), length(length) {}
};

int main(void)
{
  int number_of_vertexes, number_of_edges;

  while (std::cin >> number_of_vertexes >> number_of_edges)
  {
    if (number_of_vertexes == 0 and number_of_edges == 0)
      break;

    int total_length = 0, min_length = 0;
    std::vector<std::vector<Edge>> edges (number_of_vertexes);

    for (int i = 0; i < number_of_edges; i++)
    {
      int x, y, length;
      std::cin >> x >> y >> length;

      edges[x].emplace_back(y, x, length);
      edges[y].emplace_back(x, y, length);
      total_length += length;
    }

    std::vector<Node> priority_queues;
    // reverse_indexes[i] stores the index of id i in priority_queues
    std::vector<int> reverse_indexes;

    priority_queues.emplace_back(0, -1, 0);
    reverse_indexes.emplace_back(0);
    for (int i = 1; i < number_of_vertexes; i++)
    {
      priority_queues.emplace_back(i, -1, INT_MAX);
      reverse_indexes.emplace_back(i);
    }

    while (!priority_queues.empty())
    {
      const Node node = priority_queues.front();
      min_length += node.key;
      // std::cerr << "==========================\n";
      // std::cerr << "Node: " << node.id << ' ' << node.key << std::endl;

      // remove the minimum node
      reverse_indexes[node.id] = -1;
      priority_queues[0] = priority_queues.back();
      priority_queues.pop_back();

      for (int i = 0; i < priority_queues.size(); )
      {
        int smallest = i;
        if (2*i + 1 < priority_queues.size()
            and priority_queues[2*i+1].key < priority_queues[smallest].key)
          smallest = 2*i+1;

        if (2*i + 2 < priority_queues.size()
            and priority_queues[2*i+2].key < priority_queues[smallest].key)
          smallest = 2*i+2;

        if (smallest == i)
          break;

        const Node temp = priority_queues[i];
        priority_queues[i] = priority_queues[smallest];
        priority_queues[smallest] = temp;

        reverse_indexes[priority_queues[smallest].id] = smallest;
        reverse_indexes[priority_queues[i].id] = i;

        i = smallest;
      }

      for (const auto &edge: edges[node.id])
      {
        if (reverse_indexes[edge.x] == -1
            or edge.length >= priority_queues[reverse_indexes[edge.x]].key)
          continue;
        // std::cerr << "Edge: " << edge.y << ' ' << edge.x << ", len: " << edge.length << '\n';

        priority_queues[reverse_indexes[edge.x]].key = edge.length;

        for (int i = reverse_indexes[edge.x]; i > 0; )
        {
          if (priority_queues[i].key >= priority_queues[(i-1)/2].key)
            break;

          int parent = (i-1)/2;
          const Node temp = priority_queues[i];
          priority_queues[i] = priority_queues[parent];
          priority_queues[parent] = temp;

          reverse_indexes[priority_queues[parent].id] = parent;
          reverse_indexes[priority_queues[i].id] = i;

          i = parent;
        }

        // for (int i = 0; i < number_of_vertexes; i++)
        //   if (reverse_indexes[i] != -1 and priority_queues[reverse_indexes[i]].key != INT_MAX)
        //     std::cerr << "Index: " << i << ' ' << priority_queues[reverse_indexes[i]].key << ' ' << reverse_indexes[i] << '\n';
      }
    }

    std::cout << total_length - min_length << '\n';
  }

  return 0;
}
