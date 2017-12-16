#include <iostream>
#include <list>
#include <string>

int main(void)
{
  std::string line;
  while (std::getline(std::cin, line)) {
    std::list<char> beiju;
    std::list<char>::iterator it;

    it = beiju.begin();
    for (std::size_t i = 0; i < line.size(); i++) {
      if (line[i] == '[')
        it = beiju.begin();
      else if (line[i] == ']')
        it = beiju.end();
      else
        beiju.insert(it, line[i]);
    }

    for (it = beiju.begin(); it != beiju.end(); it++)
      std::cout << *it;
    std::cout << std::endl;
  }

  return 0;
}
