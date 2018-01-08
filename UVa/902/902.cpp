#include <iostream>
#include <map>
#include <string>

int main(void)
{
  int N;
  std::string encoded;

  while (std::cin >> N >> encoded)
  {
    std::map<std::string, int> count;

    std::string key;
    int key_freq = -1;

    for (std::string::size_type i = 0; i + N <= encoded.size(); i++)
    {
      auto first = encoded.begin() + i,
           last = encoded.begin() + i + N;

      std::string password (first, last);

      auto search = count.find(password);
      if (search != count.end())
        count[password] += 1;
      else
        count[password] = 0;

      if (count[password] > key_freq)
      {
        key = password;
        key_freq = count[password];
      }
    }

    std::cout << key << '\n';
  }

  return 0;
}
