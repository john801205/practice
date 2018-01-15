#include <climits>

#include <iostream>
#include <stack>
#include <vector>

int main(void)
{
  int number_of_numbers;

  while (std::cin >> number_of_numbers)
  {
    if (number_of_numbers == 0)
      break;

    // numbers[i] stores the input number
    std::vector<unsigned> numbers (number_of_numbers+1, 0);
    // maximum_sum[i] stores the maximum sum ending at numbers[i]
    std::vector<unsigned> maximum_sum (number_of_numbers+1, 0);
    // length[i] stores the length of maximum_sum sequence
    std::vector<unsigned> length (number_of_numbers+1, 0);
    // previous[i] stores the previous index
    std::vector<unsigned> previous (number_of_numbers+1, 0);

    unsigned max_sum = 0, max_len = UINT_MAX, max_index = 0;

    for (int i = 1; i <= number_of_numbers; i++)
    {
      std::cin >> numbers[i];

      unsigned max = maximum_sum[0],
               len = length[0],
               ind = 0;
      for (int j = 1; j < i; j++)
      {
        if (maximum_sum[j] > max
            or (maximum_sum[j] == max and length[j] < len))
        {
          max = maximum_sum[j];
          len = length[j];
          ind = j;
        }
      }

      maximum_sum[i] = numbers[i] + max;
      length[i]      = len + 1;
      previous[i]    = ind;

      if (maximum_sum[i] > max_sum
          or (maximum_sum[i] == max and length[i] < max_len))
      {
        max_sum = maximum_sum[i];
        max_len = length[i];
        max_index = i;
      }
    }

    std::stack<int> sequences;

    for (unsigned i = max_index; length[i] > 0; i = previous[i])
      sequences.push(numbers[i]);

    std::cout << sequences.top();
    sequences.pop();
    while (!sequences.empty())
    {
      std::cout << ' ' << sequences.top();
      sequences.pop();
    }
    std::cout << '\n';
  }

  return 0;
}
