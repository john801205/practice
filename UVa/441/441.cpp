#include <iostream>
#include <stack>
#include <vector>

#define LOTTO_SIZE 6

void print_stack(const std::stack<int>& stack)
{
  auto temp = stack;
  std::vector<int> list (temp.size());

  for (std::vector<int>::size_type i = list.size() - 1; !temp.empty(); i--) {
    list[i] = temp.top();
    temp.pop();
  }

  for (std::vector<int>::size_type i = 0; i < list.size(); i++) {
    if (i == 0)
      std::cout << list[i];
    else
      std::cout << ' ' << list[i];
  }
  std::cout << '\n';
}

int main(void)
{
  int k;
  bool first = true;

  while (std::cin >> k) {
    if (k == 0)
      break;

    if (!first)
      std::cout << '\n';
    first = false;

    std::vector<int> S (k);
    for (int i = 0; i < k; i++)
      std::cin >> S[i];

    std::stack<int> number_stack, index_stack;

    number_stack.push(S.front());
    index_stack.push(0);

    while (true) {
      int index = index_stack.top() + 1;

      if (number_stack.size() == LOTTO_SIZE) {
        print_stack(number_stack);
        number_stack.pop();
        index_stack.pop();
      }

      while (index == k && !index_stack.empty()) {
        index = index_stack.top() + 1;
        number_stack.pop();
        index_stack.pop();
      }

      if (index == k)
        break;

      number_stack.push(S[index]);
      index_stack.push(index);
    }
  }

  return 0;
}
