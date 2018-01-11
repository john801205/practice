#include <cmath>

#include <array>
#include <functional>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

struct Cell
{
  unsigned steps, distance;
  unsigned zero_index;
  std::array<int, 16> tables;
  std::string routes;

  Cell (unsigned s, unsigned d, unsigned z, const std::string &r, const std::array<int, 16> &t):
    steps(s), distance(d), zero_index(z), tables(t), routes(r) {}

  friend bool operator> (Cell a, Cell b)
  {
    return (a.steps+a.distance) >= (b.steps+b.distance);
  }
};

unsigned manhattan_distance(const std::array<int, 16> &tables)
{
  unsigned distance = 0;

  for (int row = 0; row < 4; row++)
  {
    for (int col = 0; col < 4; col++)
    {
      if (tables[row*4+col] == 0)
        continue;

      distance += abs(row - (tables[row*4+col]-1)/4);
      distance += abs(col - (tables[row*4+col]-1)%4);
    }
  }

  return distance;
}

unsigned long long key(const std::array<int, 16> &tables)
{
  unsigned long long k = 0, BASE = 16;

  for (int i = 0; i < 16; i++)
    k = k * BASE + tables[i];

  return k;
}

void Astar(const std::array<int, 16> &tables)
{
  std::priority_queue<Cell, std::vector<Cell>, std::greater<Cell>> queue;
  std::set<unsigned long long> set;

  unsigned distance, zero_index;

  // calculate the remaining steps
  distance = manhattan_distance(tables);

  // find the position of zero
  for (zero_index = 0; zero_index < 16; zero_index++)
    if (tables[zero_index] == 0)
      break;

  // insert into the priority queue
  queue.emplace(0, distance, zero_index, "", tables);

  while (!queue.empty())
  {
    auto cell = queue.top();
    queue.pop();

    if (cell.distance == 0)
    {
      std::cout << cell.routes << '\n';
      return;
    }

    // std::cerr << cell.steps << ' ' << cell.distance << '\n';
    // std::cerr << cell.routes << '\n';
    // for (int row = 0; row < 4; row++)
    // {
    //   for (int col = 0; col < 4; col++)
    //   {
    //     std::cerr << cell.tables[row*4+col] << ' ';
    //   }
    //   std::cerr << '\n';
    // }

    set.insert(key(cell.tables));

    unsigned row = cell.zero_index / 4,
             col = cell.zero_index % 4;

    if (row > 0 and cell.routes.back() != 'D') {
      std::array<int, 16> new_table {cell.tables};

      // move one step
      int temp = new_table[row*4+col];
      new_table[row*4+col] = new_table[(row-1)*4+col];
      new_table[(row-1)*4+col] = temp;

      unsigned distance, zero_index;
      distance = manhattan_distance(new_table);
      zero_index = (row-1)*4+col;

      auto k = key(new_table);

      if (set.count(k) == 0)
        queue.emplace(cell.steps+1, distance, zero_index, cell.routes+'U', new_table);
    }

    if (row < 3 and cell.routes.back() != 'U') {
      std::array<int, 16> new_table {cell.tables};

      // move one step
      int temp = new_table[row*4+col];
      new_table[row*4+col] = new_table[(row+1)*4+col];
      new_table[(row+1)*4+col] = temp;

      unsigned distance, zero_index;
      distance = manhattan_distance(new_table);
      zero_index = (row+1)*4+col;

      auto k = key(new_table);

      if (set.count(k) == 0)
        queue.emplace(cell.steps+1, distance, zero_index, cell.routes+'D', new_table);
    }

    if (col > 0 and cell.routes.back() != 'R') {
      std::array<int, 16> new_table {cell.tables};

      // move one step
      int temp = new_table[row*4+col];
      new_table[row*4+col] = new_table[row*4+col-1];
      new_table[row*4+col-1] = temp;

      unsigned distance, zero_index;
      distance = manhattan_distance(new_table);
      zero_index = row*4+col-1;

      auto k = key(new_table);

      if (set.count(k) == 0)
        queue.emplace(cell.steps+1, distance, zero_index, cell.routes+'L', new_table);
    }

    if (col < 3 and cell.routes.back() != 'L') {
      std::array<int, 16> new_table {cell.tables};

      // move one step
      int temp = new_table[row*4+col];
      new_table[row*4+col] = new_table[row*4+col+1];
      new_table[row*4+col+1] = temp;

      unsigned distance, zero_index;
      distance = manhattan_distance(new_table);
      zero_index = row*4+col+1;

      auto k = key(new_table);

      if (set.count(k) == 0)
        queue.emplace(cell.steps+1, distance, zero_index, cell.routes+'R', new_table);
    }
  }
}

bool is_solvable(const std::array<int, 16> &tables)
{
  int reverse_order = 0;
  int zero_bottom;

  for (int i = 0; i < 16; i++)
  {
    if (tables[i] == 0)
    {
      zero_bottom = 4 - i/4;
      continue;
    }

    for (int j = i+1; j < 16; j++)
      if (tables[j] != 0 and tables[i] > tables[j])
        reverse_order++;
  }

  return ((zero_bottom&1) == 0) == ((reverse_order&1) == 1);
}

int main(void)
{
  int number_of_puzzles;

  while (std::cin >> number_of_puzzles)
  {
    for (int puzzle = 0; puzzle < number_of_puzzles; puzzle++)
    {
      std::array<int, 16> tables = {0};

      for (int i = 0; i < 16; i++)
        std::cin >> tables[i];

      if (is_solvable(tables))
        Astar(tables);
      else
        std::cout << "This puzzle is not solvable.\n";
    }
  }

  return 0;
}
