#include <iostream>
#include <vector>
#include <stack>

int main(void)
{
  std::vector<int> numbers;
  int number;

  while (std::cin >> number)
    numbers.push_back(number);

  std::vector<int> previous (numbers.size(), -1);
  std::vector<int> results;
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
      int begin = 0, end = results.size() - 1, middle;

      while (begin < end) {
        middle = (begin + end) / 2;
        if (number <= results[middle]) {
          end = middle - 1;
        } else {
          begin = middle + 1;
        }
      }

      if (number > results[begin])
        begin++;

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
