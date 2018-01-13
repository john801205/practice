#include <algorithm>
#include <iostream>
#include <vector>

struct Line
{
  int L, R;

  Line (int L_, int R_): L(L_), R(R_) {}

  friend bool operator<(const Line &a, const Line &b)
  {
    return a.L <= b.L;
  }
};

int main(void)
{
  int number_of_cases;
  bool first = true;

  while (std::cin >> number_of_cases)
  {
    for (int case_ = 0; case_ < number_of_cases; case_++)
    {
      if (!first)
        std::cout << '\n';
      first = false;

      int M;
      std::vector<Line> lines;

      std::cin >> M;
      for (int L, R; std::cin >> L >> R; )
      {
        if (L == 0 and R == 0)
          break;

        lines.emplace_back(L, R);
      }

      std::sort(std::begin(lines), std::end(lines));

      int current = 0;
      std::vector<std::size_t> set;

      for (std::size_t i = 0; i < lines.size(); i++)
      {
        if (lines[i].L > current or lines[i].R <= current)
          continue;

        std::size_t max = i;
        for ( ;lines[i+1].L <= current; i++)
        {
          if (lines[i+1].R > lines[max].R)
            max = i+1;
        }

        set.push_back(max);
        current = lines[max].R;

        if (current >= M)
          break;
      }

      if (current >= M)
      {
        std::cout << set.size() << '\n';
        for (const auto &i: set)
          std::cout << lines[i].L << ' ' << lines[i].R << '\n';
      }
      else
      {
        std::cout << "0\n";
      }
    }
  }
  
  return 0;
}
