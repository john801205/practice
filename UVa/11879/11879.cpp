#include <iostream>
#include <string>

int main(void)
{
  std::string number;

  while (std::cin >> number and number != "0")
  {
    unsigned char dividend = 0;
    for (std::string::size_type i = 0; i < number.size(); i++)
    {
      dividend = dividend * 10 + number[i] - '0';
      dividend = dividend % 17;
    }

    if (dividend == 0)
      std::cout << "1\n";
    else
      std::cout << "0\n";
  }

  return 0;
}
