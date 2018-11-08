#include <cmath>
#include <climits>
#include <cstring>

#include <bitset>
#include <iostream>
#include <string>
#include <utility>

/* sum sums the number "num" of times "times" */
unsigned long long sum(unsigned long long num, unsigned long long times)
{
  unsigned long long result = 0;

  while (times != 0)
  {
    if ((times & 1) == 0x1)
    {
      result = (result + num) % 998244353;
    }

    num = (num + num) % 998244353;
    times >>= 1;
  }

  return result;
}

std::pair<unsigned long long, unsigned long long> solve(
          unsigned long long       dp_count[19][2][1024],
          unsigned long long       dp_sum[19][2][1024],
    const std::string             &number,
    const std::string::size_type   index,
    const bool                     less_than,
    const unsigned                 max_different_digits,
    const std::bitset<10>          masks,
    const unsigned long long       current_number
)
{
  // if we already check all the digits or we have too many different digits
  if (index == number.size() || masks.count() > max_different_digits)
  {
    if (masks.count() > max_different_digits)
      return {0, 0};
    else
      return {1, 0};
  }

  const unsigned      index_less_than = (less_than? 1: 0);
  const unsigned long index_masks     = masks.to_ulong();

  if (dp_count[index][index_less_than][index_masks] != ULLONG_MAX)
  {
    return {
      dp_count[index][index_less_than][index_masks],
      dp_sum[index][index_less_than][index_masks]
    };
  }

  unsigned long long result_count = 0;
  unsigned long long result_sum   = 0;
  unsigned long long zeros = std::pow(10, number.size()-index-1);

  const unsigned     limit = (less_than? number[index]-'0': 9);

  for (unsigned i = 0; i <= limit; i++)
  {
    const bool      new_less_than = (i == limit? less_than: false);
    std::bitset<10> new_masks     = masks;

    if (current_number != 0 || i != 0)
      new_masks.set(i);

    auto result = solve(dp_count,
                        dp_sum,
                        number,
                        index+1,
                        new_less_than,
                        max_different_digits,
                        new_masks,
                        current_number*10+i);

    // result.first stores how many numbers satisfy the constraints with
    //              with know different digits
    // result.second stores their sums
    result_count += result.first;
    result_sum = (result_sum + result.second) % 998244353;
    result_sum = (result_sum + sum(i*zeros, result.first)) % 998244353;
  }

  dp_count[index][index_less_than][index_masks] = result_count;
  dp_sum[index][index_less_than][index_masks] = result_sum;
  return {result_count, result_sum};
}

unsigned long long solve(
    const unsigned long long number,
    const unsigned           max_different_digits
)
{
  unsigned long long dp_count[19][2][1024];
  unsigned long long dp_sum[19][2][1024];

  memset(dp_count, -1, sizeof(dp_count));
  memset(dp_sum, -1, sizeof(dp_sum));

  auto r = solve(dp_count,
                 dp_sum,
                 std::to_string(number),
                 0,
                 true,
                 max_different_digits,
                 std::bitset<10>{},
                 0);

  return r.second;
}

int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // l, r: the borders of the segment
  // k   : the maximum number of different digits
  unsigned long long l, r, k;
  std::cin >> l >> r >> k;

  std::cout << (solve(r, k) + 998244353 - solve(l-1, k)) % 998244353 << '\n';

  return 0;
}
