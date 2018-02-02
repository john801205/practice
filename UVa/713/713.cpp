#include <iostream>
#include <string>

std::string add(const std::string &a, const std::string &b)
{
  std::string::size_type length = std::max(a.size(), b.size());
  std::string result (length, 0);
  unsigned carry = 0;

  for (std::string::size_type i = 0; i < length; i++)
  {
    result[i] = carry;

    if (i < a.size())
      result[i] += a[i] - '0';

    if (i < b.size())
      result[i] += b[i] - '0';

    carry = result[i] / 10;
    result[i] = result[i] % 10 + '0';
  }

  if (carry != 0)
    result += carry + '0';

  for (std::string::size_type i = 0; i < result.size(); i++)
    if (result[i] != '0')
      return result.substr(i);

  return std::string (1, '0');
}

int main(void)
{
  int number_of_test_cases;

  std::cin >> number_of_test_cases;
  for (int case_ = 0; case_ < number_of_test_cases; case_++)
  {
    std::string a, b;
    std::cin >> a >> b;

    std::cout << add(a, b) << '\n';
  }

  return 0;
}
