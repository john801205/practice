#include <iostream>
#include <vector>
#include <string>
#include <sstream>

int main(void)
{
  int N;

  while (std::cin >> N) {
    std::string line;
    std::getline(std::cin, line);
    for (int i = 0; i < N; ++i) {
      std::stringstream line_stream;

      std::getline(std::cin, line);
      std::getline(std::cin, line);
      line_stream << line;

      std::vector<int> indexes;
      int index;
      while (line_stream >> index)
        indexes.push_back(index);

      std::getline(std::cin, line);
      line_stream.clear(); // need to clear the EOF bit
      line_stream << line;

      std::string *numbers = new std::string[indexes.size()];
      for (auto it=indexes.begin(); it != indexes.end(); ++it)
        line_stream >> numbers[*it - 1];

      if (i != 0)
        std::cout << std::endl;

      for (unsigned index = 0; index < indexes.size(); ++index)
        std::cout << numbers[index] << std::endl;

      delete[] numbers;
    }
  }

  return 0;
}
