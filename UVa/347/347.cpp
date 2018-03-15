#include <iostream>
#include <string>
#include <vector>

bool is_duplicate_number(unsigned number)
{
  std::vector<bool> used (10, false);

  while (number != 0)
  {
    unsigned digit = number % 10;

    if (used[digit])
      return true;

    used[digit] = true;
    number /= 10;
  }

  return false;
}

bool is_runaround_number(const unsigned number)
{
  // check if any digit is duplicated
  if (is_duplicate_number(number))
    return false;

  // check if the sequence is valid
  const std::string            number_string = std::to_string(number);
  const std::string::size_type size          = number_string.size();
        std::string::size_type i             = 0;
        std::string::size_type count         = 0;
        std::vector<bool>      used (size, false);

  while (!used[i])
  {
    used[i] = true;
    i = (i + number_string[i] - '0') % size;
    count++;
  }

  // check if the sequence return to the first digits
  if (i != 0)
  {
    return false;
  }

  // check if all digits have been used
  return count == size;
}

int main(void)
{
  std::ios::sync_with_stdio(false);

  std::vector<unsigned> map (10000000);

  for (unsigned i = 9876543; i > 9; i--)
  {
    if (is_runaround_number(i))
    {
      map[i] = i;
    }
    else
    {
      map[i] = map[i+1];
    }
  }

  unsigned number, case_ = 0;

  while (std::cin >> number && number != 0)
  {
    case_++;
    std::cout << "Case " << case_ << ": " << map[number] << '\n';
  }

  return 0;
}
