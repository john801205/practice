#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<unsigned> convert_to_digits(const std::string &x)
{
  std::vector<unsigned> result (x.size(), 0);

  for (std::string::size_type i = 0; i < x.size(); i++)
  {
    if (x[i] >= '0' and x[i] <= '9')
      result[i] = x[i] - '0';
    else
      result[i] = x[i] - 'A' + 10;
  }

  return result;
}

unsigned long long to_decimal(const std::vector<unsigned> &digits,
                              const unsigned               base)
{
  unsigned long long result = 0;

  for (std::vector<unsigned>::size_type i = 0; i < digits.size(); i++)
    result = result * base + digits[i];

  return result;
}

int main(void)
{
  std::string a, b;

  while (std::cin >> a >> b)
  {
    std::vector<unsigned> a_digits = convert_to_digits(a),
                          b_digits = convert_to_digits(b);

    auto a_max = std::max_element(std::begin(a_digits),
                                  std::end(a_digits));
    auto b_max = std::max_element(std::begin(b_digits),
                                  std::end(b_digits));

    bool equal = false;

    for (auto a_base = std::max(*a_max+1, 2U); a_base <= 36U and not equal; a_base++)
    {
      for (auto b_base = std::max(*b_max+1, 2U); b_base <= 36U and not equal; b_base++)
      {
        if (to_decimal(a_digits, a_base) == to_decimal(b_digits, b_base))
        {
          equal = true;
          std::cout << a << " (base " << a_base << ") = "
                    << b << " (base " << b_base << ")\n";
        }
      }
    }

    if (not equal)
    {
      std::cout << a << " is not equal to " << b
                << " in any base 2..36\n";
    }
  }

  return 0;
}
