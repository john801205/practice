#include <iostream>

long long solve(
    const unsigned long long x,
    const unsigned long long y,
    const unsigned long long moves
)
{
  if (std::max(x, y) > moves)
    return -1;

  if ((x & 0x1) != (y & 0x1))
    return moves-1;
  else if ((x & 0x1) == (moves & 0x1))
    return moves;
  else
    return moves-2;
}

int main()
{
  int number_of_queries;
  std::cin >> number_of_queries;

  for (int query = 0; query < number_of_queries; query++)
  {
    // x    : x-coordinate of the destination point
    // y    : y-coordinate of the destination point
    // moves: the number of moves
    unsigned long long x, y, moves;
    std::cin >> x >> y >> moves;

    std::cout << solve(x, y, moves) << '\n';
  }


  return 0;
}
