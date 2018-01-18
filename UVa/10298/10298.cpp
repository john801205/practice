#include <iostream>
#include <sstream>
#include <string>

int main(void)
{
  std::string line;

  while (std::cin >> line)
  {
    if (line == ".")
      break;

    for (std::string::size_type len = 1; len <= line.size(); len++)
    {
      if (line.size() % len != 0)
        continue;

      bool equal = true;

      // index i stores the position in substr [0, len)
      // index j stores the position in line
      // we check if line[i] equals to line[j]
      for (std::string::size_type j = len; j < line.size(); j+=len)
      {
        if (line.compare(j, len, line, 0, len) != 0)
        {
          equal = false;
          break;
        }
      }

      if (equal)
      {
        std::cout << line.size()/len << '\n';
        break;
      }
    }
  }

  return 0;
}
