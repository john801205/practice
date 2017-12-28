#include <iostream>
#include <vector>
#include <stack>

int main(void)
{
  std::vector<int> numbers;
  int number;

  while (std::cin >> number)
    numbers.push_back(number);

  // previous[i] stores the index of previous smaller elemment for numbers[i]
  std::vector<int> previous (numbers.size(), -1);
  // results[i] stores the minimum ending value of length-i LIS
  std::vector<int> results;
  // result_indexes[i] stores the index of results[i] in numbers
  std::vector<std::vector<int>::size_type> result_indexes;

  for (std::vector<int>::size_type i = 0; i < numbers.size(); i++) {
    const int& number = numbers[i];

    if (results.size() == 0) {
      previous[i] = -1;
      results.push_back(number);
      result_indexes.push_back(i);
    } else if (number > results.back()) {
      previous[i] = result_indexes.back();
      results.push_back(number);
      result_indexes.push_back(i);
    } else {
      std::vector<int>::size_type begin = 0, end = results.size() - 1, middle;

      while (begin < end) {
        middle = begin + (end-begin)/2;
        if (number <= results[middle]) {
          end = middle;
        } else {
          begin = middle + 1;
        }
      }

      if (begin > 0)
        previous[i] = result_indexes[begin - 1];
      else
        previous[i] = -1;
      results[begin] = number;
      result_indexes[begin] = i;
    }
  }

  int index = result_indexes.back();
  std::stack<int> stack;
  while (index != -1) {
    stack.push(numbers[index]);
    index = previous[index];
  }

  std::cout << stack.size() << '\n';
  std::cout << "-\n";
  while (!stack.empty()) {
    std::cout << stack.top() << '\n';
    stack.pop();
  }

  return 0;
}
