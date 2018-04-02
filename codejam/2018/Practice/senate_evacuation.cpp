#include <iostream>
#include <queue>
#include <vector>

struct Party
{
  char name;
  int  persons;

  Party(char name, int persons): name(name), persons(persons) {}

  friend bool operator> (const Party &lhs, const Party &rhs)
  {
    return lhs.persons > rhs.persons;
  }
};


std::vector<Party>::size_type parent(std::vector<Party>::size_type i)
{
  return (i-1) / 2;
}

std::vector<Party>::size_type left(std::vector<Party>::size_type i)
{
  return i*2 + 1;
}

std::vector<Party>::size_type right(std::vector<Party>::size_type i)
{
  return i*2 + 2;
}

int main(void)
{
  int number_of_tests;

  std::cin >> number_of_tests;

  for (int test = 1; test <= number_of_tests; test++)
  {
    std::vector<Party> queue;
    int number_of_parties, number_of_total_persons;

    std::cin >> number_of_parties;
    number_of_total_persons = 0;

    for (int i = 0; i < number_of_parties; i++)
    {
      int number_of_persons;
      std::cin >> number_of_persons;

      number_of_total_persons += number_of_persons;
      queue.emplace_back('A' + i, number_of_persons);

      std::vector<Party>::size_type j = queue.size()-1;

      while (j != 0 && queue[j] > queue[parent(j)])
      {
        std::swap(queue[j], queue[parent(j)]);
        j = parent(j);
      }
    }

    std::cout << "Case #" << test << ":";
    while (!queue.empty())
    {
      int count = 0;
      std::cout << ' ';

      do
      {
        count++;

        std::cout << queue[0].name;
        queue[0].persons -= 1;
        number_of_total_persons -= 1;

        if (queue[0].persons == 0)
        {
          std::swap(queue[0], queue.back());
          queue.pop_back();
        }

        std::vector<Party>::size_type index = 0;
        while (true)
        {
          std::vector<Party>::size_type next = index;

          if (left(index) < queue.size() && queue[left(index)] > queue[next])
          {
            next = left(index);
          }

          if (right(index) < queue.size() && queue[right(index)] > queue[next])
          {
            next = right(index);
          }

          if (index == next)
          {
            break;
          }
          else
          {
            std::swap(queue[index], queue[next]);
            index = next;
          }
        }
      }
      while (count < 2 && !queue.empty() && (queue.size() == 1 || (std::max(queue[0].persons-1, queue[1].persons)*2 <= number_of_total_persons-1)));
    }

    std::cout << '\n';
  }

  return 0;
}
