#include <iostream>

int main(void)
{
  std::string::size_type n;
  std::string            string;

  std::cin >> n >> string;

  for (std::string::size_type i = 0; i+1 < n; i++)
  {
    if (string[i] != string[i+1])
    {
      std::cout << "YES\n";
      std::cout << string.substr(i, 2);
      return 0;
    }
  }

  std::cout << "NO";
  return 0;
}
