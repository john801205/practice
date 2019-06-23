#include <climits>
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

int findAugmentPath(      std::unordered_map<int, std::unordered_map<int, int>> &residual,
                    const int number_of_nodes,
                    const int source,
                    const int target,
                          std::vector<int> &path)
{
  std::queue<int> queue({source});
  std::vector<bool> visited(number_of_nodes+1, false);
  std::vector<int> parents(number_of_nodes+1);

  bool found = false;
  visited[source] = true;
  parents[source] = source;

  while (!found && !queue.empty())
  {
    const auto node = queue.front();
    queue.pop();

    for (const auto &itr: residual[node])
    {
      const auto &neighbor = itr.first;
      if (visited[neighbor])
        continue;
      if (residual[node][neighbor] == 0)
        continue;

      parents[neighbor] = node;
      visited[neighbor] = true;
      queue.push(neighbor);

      if (neighbor == target)
        found = true;
    }
  }

  if (!found)
    return 0;

  std::vector<int> result({target});
  int minCap = INT_MAX, node = target;

  while (parents[node] != node)
  {
    const auto &parent = parents[node];

    minCap = std::min(minCap, residual[parent][node]);
    result.emplace_back(parent);
    node = parent;
  }

  std::reverse(result.begin(), result.end());
  path = result;

  return minCap;
}

int solve(      std::unordered_map<int, std::unordered_map<int, int>> &capacity,
          const int number_of_nodes,
          const int source,
          const int target)
{
  std::unordered_map<int, std::unordered_map<int, int>> flow;
  std::unordered_map<int, std::unordered_map<int, int>> residual;

  for (const auto &itr1: capacity)
  {
    const auto &n1 = itr1.first;
    const auto &edges = itr1.second;
    for (const auto &itr2: edges)
    {
      const auto &n2 = itr2.first;
      const auto &cap = itr2.second;
      residual[n1][n2] = cap;
      residual[n2][n1] = cap;
    }
  }

  int result = 0;
  std::vector<int> path;
  int minCap = findAugmentPath(residual, number_of_nodes, source, target, path);
  while (minCap != 0)
  {
    result += minCap;
    for (std::vector<int>::size_type i = 1; i < path.size(); i++)
    {
      const auto parent = path[i-1], node = path[i];
      flow[parent][node] += minCap;

      if (flow[parent][node] + flow[node][parent] > capacity[parent][node])
        flow[node][parent] = capacity[parent][node] - flow[parent][node];

      residual[parent][node] = capacity[parent][node] - flow[parent][node];
      residual[node][parent] = capacity[node][parent] - flow[node][parent];
    }

    minCap = findAugmentPath(residual, number_of_nodes, source, target, path);
  }

  return result;
}

int main()
{
  int number_of_nodes, network = 1;
  std::cin >> number_of_nodes;

  while (number_of_nodes != 0)
  {
    int source, target, number_of_connections;
    std::cin >> source >> target >> number_of_connections;

    std::unordered_map<int, std::unordered_map<int, int>> capacity;
    for (int i = 0; i < number_of_connections; i++)
    {
      int s, t, c; std::cin >> s >> t >> c;
      capacity[s][t] += c;
      capacity[t][s] += c;
    }

    const auto bandwidth = solve(capacity, number_of_nodes, source, target);
    std::cout << "Network " << network << '\n';
    std::cout << "The bandwidth is " << bandwidth << ".\n\n";

    network++;
    std::cin >> number_of_nodes;
  }

  return 0;
}
