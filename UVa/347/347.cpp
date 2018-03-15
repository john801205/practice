#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

bool is_duplicate_number(const std::string &number)
{
  std::vector<bool> used (10, false);

  for (const auto &digit: number)
  {
    if (used[digit - '0'])
      return true;

    used[digit - '0'] = true;
  }

  return false;
}

bool is_runaround_number(const std::string &number)
{
  // check if any digit is duplicated
  if (is_duplicate_number(number))
    return false;

  // check if the sequence is valid
  const std::string::size_type size  = number.size();
        std::vector<bool>      status (size, false);
        std::string::size_type i     = 0;
        std::string::size_type count = 0;

  while (!status[i])
  {
    status[i] = true;
    i = (i + number[i] - '0') % size;
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

bool is_runaround_number(const unsigned number)
{
  return is_runaround_number(std::to_string(number));
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
