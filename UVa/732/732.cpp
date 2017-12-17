#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <vector>

void transform(std::queue<char> source, std::queue<char> target, std::stack<char> stack, std::vector<char> operations)
{
  while (!source.empty()) {
    char c = source.front();

    stack.push(c);
    operations.push_back('i');
    source.pop();

    if (c == target.front())
      break;
  }

  if (stack.top() != target.front())
    return;

  if (!source.empty()) {
    transform(source, target, stack, operations);

    while (!stack.empty() && !target.empty() && stack.top() == target.front()) {
      target.pop();
      stack.pop();
      operations.push_back('o');
      transform(source, target, stack, operations);
    }
  } else {
    while (!stack.empty() && !target.empty() && stack.top() == target.front()) {
      stack.pop();
      target.pop();
      operations.push_back('o');
    }

    if (!stack.empty() || !target.empty())
      return;

    for (std::vector<char>::size_type i = 0; i < operations.size(); i++) {
      if (i != 0)
        std::cout << ' ';
      std::cout << operations[i];
    }
    std::cout << std::endl;
  }
}

int main(void)
{
  std::string source, target;

  while (std::cin >> source >> target) {
    std::queue<char> source_queue, target_queue;
    std::stack<char> stack;
    std::vector<char> operations;

    for (auto it = source.begin(); it != source.end(); ++it)
      source_queue.push(*it);

    for (auto it = target.begin(); it != target.end(); ++it)
      target_queue.push(*it);

    std::cout << '[' << std::endl;
    transform(source_queue, target_queue, stack, operations);
    std::cout << ']' << std::endl;
  }

  return 0;
}
