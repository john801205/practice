#include <climits>

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

class PriorityQueue
{
  private:
    // keys stores in the increasing order
    std::vector<unsigned> keys;
    // ids[i] stores the id of keys[i]
    std::vector<unsigned> ids;
    // indexes[i] stores the index of id i in keys
    std::unordered_map<unsigned, std::vector<unsigned>::size_type> indexes;

    inline std::vector<unsigned>::size_type parent(std::vector<unsigned>::size_type i)
    {
      if (i == 0)
        std::cerr << "parent(" << i << ") is invalid\n";
      return (i-1)/2;
    }

    inline std::vector<unsigned>::size_type left(std::vector<unsigned>::size_type i)
    {
      return i*2+1;
    }

    inline std::vector<unsigned>::size_type right(std::vector<unsigned>::size_type i)
    {
      return i*2+2;
    }

  public:
    PriorityQueue(void): keys(), ids(), indexes() {}

    void decreaseKey(const unsigned id, const unsigned key)
    {
      keys[indexes.at(id)] = key;

      for (unsigned i = indexes[id];
           i > 0 and keys[parent(i)] > keys[i];
           i = parent(i))
      {
        std::swap(indexes[ids[parent(i)]], indexes[ids[i]]);
        std::swap(ids[parent(i)], ids[i]);
        std::swap(keys[parent(i)], keys[i]);
      }
    }

    void push(const unsigned id, const unsigned key)
    {
      indexes[id] = keys.size();
      keys.push_back(UINT_MAX);
      ids.push_back(id);

      decreaseKey(id, key);
    }

    void pop(unsigned &id, unsigned &key)
    {
      // pop the element with smallest key
      id = ids[0];
      key = keys[0];

      // move the last one to the front
      ids[0] = ids.back();
      keys[0] = keys.back();
      indexes[ids[0]] = 0;

      // shrink 1 size
      ids.pop_back();
      keys.pop_back();
      indexes.erase(id);

      for (std::vector<unsigned>::size_type i = 0; i < keys.size();)
      {
        std::vector<unsigned>::size_type smallest = i;

        if (left(i) < keys.size() and keys[left(i)] < keys[smallest])
          smallest = left(i);
        if (right(i) < keys.size() and keys[right(i)] < keys[smallest])
          smallest = right(i);

        if (smallest == i)
          break;

        std::swap(indexes[ids[smallest]], indexes[ids[i]]);
        std::swap(ids[smallest], ids[i]);
        std::swap(keys[smallest], keys[i]);

        i = smallest;
      }

    }

    bool empty(void) const
    {
      return keys.empty();
    }

    bool exist(unsigned id) const
    {
      return indexes.find(id) != indexes.end();
    }

    unsigned getKey(unsigned id) const
    {
      return keys[indexes.at(id)];
    }

    void print(void) const
    {
      std::cerr << "====================\n";
      for (std::vector<unsigned>::size_type i = 0; i < keys.size(); i++)
        std::cerr << ids[i] << ' ' << keys[i] << '\n';

      for (const auto &n: indexes)
        std::cerr << "Key: " << n.first << ", index: " << n.second << '\n';
    }
};

struct Edge
{
  const unsigned x, y, weight;

  Edge(unsigned x, unsigned y, unsigned weight): x(x), y(y), weight(weight) {}
};

int main(void)
{
  unsigned number_of_crossings,
           number_of_streets,
           number_of_queries;
  unsigned case_ = 1;

  while (std::cin >> number_of_crossings
                  >> number_of_streets
                  >> number_of_queries)
  {
    if (number_of_crossings == 0
        and number_of_streets == 0
        and number_of_queries == 0)
      break;

    std::cout << (case_ == 1 ? "": "\n") << "Case #" << case_ << '\n';
    case_++;

    std::vector<std::vector<Edge>> edges (number_of_crossings+1);
    for (unsigned i = 0; i < number_of_streets; i++)
    {
      unsigned x, y, weight;
      std::cin >> x >> y >> weight;

      edges[x].emplace_back(y, x, weight);
      edges[y].emplace_back(x, y, weight);
    }

    for (unsigned query = 1; query <= number_of_queries; query++)
    {
      PriorityQueue queue;
      std::vector<unsigned> parents (number_of_crossings+1, 0);
      unsigned source, target;

      std::cin >> source >> target;

      for (unsigned i = 1; i <= number_of_crossings; i++)
        queue.push(i, UINT_MAX);
      queue.decreaseKey(source, 0);

      while (!queue.empty())
      {
        unsigned id, key;
        queue.pop(id, key);

        // if find the target
        if (id == target)
          break;

        // if no more connected
        if (key == UINT_MAX)
          break;

        for (const auto &edge: edges[id])
        {
          if (queue.exist(edge.x)
              and edge.weight < queue.getKey(edge.x))
          {
            queue.decreaseKey(edge.x, edge.weight);
            parents[edge.x] = id;
          }
        }
      }

      if (parents[target] != 0)
      {
        unsigned max_weight = 0;

        for (unsigned i = target; parents[i] != 0; i = parents[i]) 
          for (const auto &edge: edges[i])
            if (edge.x == parents[i] and edge.weight > max_weight)
              max_weight = edge.weight;

        std::cout << max_weight << '\n';
      }
      else
      {
        std::cout << "no path\n";
      }
    }
  }

  return 0;
}
