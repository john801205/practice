#include <climits>

#include <algorithm>
#include <iostream>
#include <vector>

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
      std::cin >> M;

      // lines[i] stores the rightmost endpoint of segments starting
      // from index i. if the left endpoint of segment is negative,
      // we store its rightmost endpoint at lines[0] and left endpoint
      // at zero_left
      int zero_left;
      std::vector<int> lines(M, INT_MIN);

      for (int L, R; std::cin >> L >> R; )
      {
        if (L == 0 and R == 0)
          break;

        // if not overlapping with [0, M]
        if (R <= 0 or L >= M)
          continue;

        int orig_L = L;
        if (L <= 0)
          L = 0;

        if (R > lines[L])
        {
          lines[L] = R;
          if (L == 0)
            zero_left = orig_L;
        }
      }

      std::size_t left = 0, right = 0;
      std::vector<std::size_t> set;

      while (left <= right and right < unsigned(M))
      {
        int max = INT_MIN;
        std::size_t max_index;

        for (std::size_t i = left; i <= right; i++)
        {
          if (lines[i] > max)
          {
            max = lines[i];
            max_index = i;
          }
        }

        if (max == INT_MIN)
          break;

        set.push_back(max_index);

        left = right+1;
        right = max;
      }

      if (right >= unsigned(M))
      {
        std::cout << set.size() << '\n';
        for (const auto &i: set)
        {
          if (i == 0)
            std::cout << zero_left << ' ' << lines[i] << '\n';
          else
            std::cout << i << ' ' << lines[i] << '\n';
        }
      }
      else
      {
        std::cout << "0\n";
      }
    }
  }

  return 0;
}
