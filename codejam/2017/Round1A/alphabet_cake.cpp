#include <iostream>
#include <string>
#include <vector>

int main(void)
{
  int number_of_tests;
  std::cin >> number_of_tests;

  for (int test = 1; test <= number_of_tests; test++)
  {
    int R, C;
    std::cin >> R >> C;

    std::vector<char> first (R);
    std::vector<std::string> cake (R);
    for (int i = 0; i < R; i++)
    {
      std::cin >> cake[i];

      for (int j = 0; j < C; j++)
      {
        if (cake[i][j] != '?')
        {
          first[i] = cake[i][j];
          break;
        }
      }
    }

    int last_row = 0;
    for (int i = 0; i < R; i++)
    {
      if (first[i] == 0)
      {
        continue;
      }

      last_row = i;
      char current = first[i];
      for (int j = 0; j < C; j++)
      {
        if (cake[i][j] == '?')
        {
          cake[i][j] = current;
        }
        else
        {
          current = cake[i][j];
        }
      }

      for (int j = i-1; j >= 0 && first[j] == 0; j--)
      {
        cake[j] = cake[i];
      }
    }

    for (int i = last_row+1; i < R; i++)
    {
      cake[i] = cake[last_row];
    }

    std::cout << "Case #" << test << ":\n";
    for (int i = 0; i < R; i++)
      std::cout << cake[i] << '\n';
  }
  return 0;
}
