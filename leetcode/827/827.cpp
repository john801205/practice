#include <cassert>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution
{
  public:
    int largestIsland(const std::vector<std::vector<int>> &grid)
    {
      std::vector<std::vector<int>> ids = grid;
      std::unordered_map<int, int> maps;
      int largest = 0, id = 0;

      for (std::vector<int>::size_type i = 0; i < grid.size(); i++)
      {
        for (std::vector<int>::size_type j = 0; j < grid[i].size(); j++)
        {
          ids[i][j] = 0;
        }
      }

      for (std::vector<int>::size_type i = 0; i < grid.size(); i++)
      {
        for (std::vector<int>::size_type j = 0; j < grid[i].size(); j++)
        {
          if (grid[i][j] == 0)
            continue;
          if (ids[i][j] != 0)
            continue;

          id++;
          maps[id] = dfs(grid, ids, i, j, id);
          largest = std::max(largest, maps[id]);
        }
      }

      // for (const auto itr: maps)
      //   std::cerr << itr.first << '\t' << itr.second << '\n';

      // for (std::vector<int>::size_type i = 0; i < grid.size(); i++)
      // {
      //   for (std::vector<int>::size_type j = 0; j < grid[i].size(); j++)
      //     std::cerr << ids[i][j] << ' ';
      //   std::cerr << '\n';
      // }

      for (std::vector<int>::size_type i = 0; i < grid.size(); i++)
      {
        for (std::vector<int>::size_type j = 0; j < grid[i].size(); j++)
        {
          if (grid[i][j] != 0)
            continue;

          int count = 1;
          std::unordered_set<int> set;

          if (i > 0 && ids[i-1][j] != 0)
            set.emplace(ids[i-1][j]);
          if (i+1 < grid.size() && ids[i+1][j] != 0)
            set.emplace(ids[i+1][j]);
          if (j > 0 && ids[i][j-1] != 0)
            set.emplace(ids[i][j-1]);
          if (j+1 < grid[i].size() && ids[i][j+1] != 0)
            set.emplace(ids[i][j+1]);

          for (const auto &id: set)
            count += maps[id];

          largest = std::max(largest, count);
        }
      }

      return largest;
    }

    int dfs(const std::vector<std::vector<int>> &grid,
                  std::vector<std::vector<int>> &ids,
            const std::vector<int>::size_type    row,
            const std::vector<int>::size_type    col,
            const int                            id)
    {
      if (grid[row][col] == 0)
        return 0;

      int count = 1;
      ids[row][col] = id;

      if (row > 0 && ids[row-1][col] == 0)
        count += dfs(grid, ids, row-1, col, id);
      if (row+1 < grid.size() && ids[row+1][col] == 0)
        count += dfs(grid, ids, row+1, col, id);
      if (col > 0 && ids[row][col-1] == 0)
        count += dfs(grid, ids, row, col-1, id);
      if (col+1 < grid[row].size() && ids[row][col+1] == 0)
        count += dfs(grid, ids, row, col+1, id);

      return count;
    }
};

int main()
{
  Solution s;
  assert(s.largestIsland({{1,0},{0,1}}) == 3);
  assert(s.largestIsland({{1,1},{1,0}}) == 4);
  assert(s.largestIsland({{1,1},{1,1}}) == 4);
  return 0;
}
