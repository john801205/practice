#include <iostream>
#include <stack>
#include <queue>

int main(void)
{
  int number_of_operations;

  while (std::cin >> number_of_operations) {
    std::stack<int> stack;
    std::queue<int> queue;
    std::priority_queue<int> priority_queue;

    bool is_stack = true,
         is_queue = true,
         is_priority_queue = true;

    for (int i = 0, op, num; i < number_of_operations; i++) {
      std::cin >> op >> num;
      if (op == 1) {
        if (is_stack)
          stack.push(num);

        if (is_queue)
          queue.push(num);

        if (is_priority_queue)
          priority_queue.push(num);
      } else {
        if (is_stack && !stack.empty() && stack.top() == num)
          stack.pop();
        else
          is_stack = false;

        if (is_queue && !queue.empty() && queue.front() == num)
          queue.pop();
        else
          is_queue = false;

        if (is_priority_queue
            && !priority_queue.empty()
            && priority_queue.top() == num)
          priority_queue.pop();
        else
          is_priority_queue = false;
      }
    }

    if ((is_stack && is_queue)
         || (is_stack && is_priority_queue)
         || (is_queue && is_priority_queue))
      std::cout << "not sure\n";
    else if (is_stack)
      std::cout << "stack\n";
    else if (is_queue)
      std::cout << "queue\n";
    else if (is_priority_queue)
      std::cout << "priority queue\n";
    else
      std::cout << "impossible\n";
  }

  return 0;
}
