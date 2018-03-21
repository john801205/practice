#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Solution
{
  public:
    int maxProduct(std::vector<std::string> &words)
    {
      std::vector<unsigned> numbers;
      std::string::size_type max = 0;

      for (const auto &word: words)
      {
        unsigned number = 0;
        for (const auto &character: word)
        {
          number |= 1 << (character - 'a');
        }

        numbers.push_back(number);
      }

      for (std::vector<unsigned>::size_type i = 0; i < numbers.size(); i++)
      {
        for (std::vector<unsigned>::size_type j = i+1; j < numbers.size(); j++)
        {
          if ((numbers[i] & numbers[j]) == 0)
          {
            max = std::max(max, words[i].size() * words[j].size());
          }
        }
      }

      return max;
    }
};

int main(void)
{
  return 0;
}
