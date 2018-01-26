#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>

#define MAX 5842
const std::vector<unsigned long> primes = {2, 3, 5, 7};

int main(void)
{
  std::vector<unsigned long> indexes;
  std::unordered_set<unsigned long> numbers;
  std::priority_queue<unsigned long,
                      std::vector<unsigned long>,
                      std::greater<unsigned long>> queues;

  numbers.insert(1);
  queues.push(1);

  while (indexes.size() != MAX)
  {
    auto number = queues.top();
    indexes.push_back(number);

    for (const auto &prime: primes)
    {
      if (numbers.find(number * prime) == numbers.end())
      {
        numbers.insert(number * prime);
        queues.push(number * prime);
      }
    }

    queues.pop();
  }

  int query;

  while (std::cin >> query and query != 0)
  {
    std::cout << "The " << query;

    if (query % 10 == 1 and query % 100 != 11)
      std::cout << "st";
    else if (query % 10 == 2 and query % 100 != 12)
      std::cout << "nd";
    else if (query % 10 == 3 and query % 100 != 13)
      std::cout << "rd";
    else
      std::cout << "th";

    std::cout << " humble number is " << indexes.at(query-1) << ".\n";
  }

  return 0;
}
