#include <climits>
#include <cstring>

#include <iostream>
#include <string>

unsigned long long solve(
          unsigned long long      dp[19][2][4],
    const std::string            &digits,
    const std::string::size_type  index,
    const bool                    less_than,
    const unsigned                non_zero_count
)
{
  // Once we browse all digits, we check the value of non_zero_count
  // to determine if this number is legel. Also, we can terminate the
  // process early if we find it contains more than three non-zero digits.
  if (index == digits.size() || non_zero_count > 3)
  {
    if (non_zero_count <= 3)
      return 1;
    else
      return 0;
  }

  // convert the boolean value into an index in array
  const unsigned index_less_than = (less_than? 1: 0);

  // return the result immediately if we calculated it before
  if (dp[index][index_less_than][non_zero_count] != ULLONG_MAX)
  {
    return dp[index][index_less_than][non_zero_count];
  }

  // If less_than is true, we can only put some digit less than the
  // original one into this index. Otherwise, we can put any digit.
  const unsigned limit = (less_than? digits[index]-'0': 9);
  unsigned long long result = 0;

  for (unsigned i = 0; i <= limit; i++)
  {
    // If this index is put the largest digit, the value of next index
    // should be less than the original digit. Otherwise, it can be any
    // value.
    const bool smaller = (i == limit? less_than: false);

    // recursively into the next index
    if (i != 0)
      result += solve(dp, digits, index+1, smaller, non_zero_count+1);
    else
      result += solve(dp, digits, index+1, smaller, non_zero_count);
  }

  // stores the result into dp array and return it
  dp[index][index_less_than][non_zero_count] = result;
  return result;
}

/* solve returns the number of classy integer less than the
 * argument number. Classy integer is some integer whose decimal
 * representation contains no more than three non-zero digits. */
unsigned long long solve(const unsigned long long number)
{
  unsigned long long dp[19][2][4];
  memset(dp, -1, sizeof(dp));

  return solve(dp, std::to_string(number), 0, true, 0);
}

int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int number_of_segments;
  std::cin >> number_of_segments;

  for (int i = 0; i < number_of_segments; i++)
  {
    unsigned long long L, R;
    std::cin >> L >> R;

    std::cout << solve(R) - solve(L-1) << '\n';
  }

  return 0;
}
