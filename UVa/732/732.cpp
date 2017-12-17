#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <vector>

void transform(const std::string &source,
               const std::string &target,
               std::string::size_type source_index,
               std::string::size_type target_index,
               std::stack<char> &stack,
               std::vector<char> &operations)
{
  if (source_index == source.length() && target_index == target.length()) {
    for (std::vector<char>::size_type i = 0; i < operations.size(); i++) {
      if (i != 0)
        std::cout << ' ';
      std::cout << operations[i];
    }
    std::cout << std::endl;

    return;
  }

  if (source_index < source.length()) {
    char c = source[source_index];
    stack.push(c);
    operations.push_back('i');

    transform(source, target, source_index+1, target_index, stack, operations);

    stack.pop();
    operations.pop_back();
  }

  if (!stack.empty() && stack.top() == target[target_index]) {
    char c = stack.top();
    stack.pop();
    operations.push_back('o');

    transform(source, target, source_index, target_index+1, stack, operations);

    stack.push(c);
    operations.pop_back();
  }
}

int main(void)
{
  std::string source, target;

  while (std::cin >> source >> target) {
    std::stack<char> stack;
    std::vector<char> operations;

    std::cout << '[' << std::endl;
    transform(source, target, 0, 0, stack, operations);
    std::cout << ']' << std::endl;
  }

  return 0;
}
