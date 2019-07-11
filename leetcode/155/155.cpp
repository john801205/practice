#include <cassert>
#include <stack>

class MinStack
{
  private:
    std::stack<int> Stack;
    std::stack<int> Min;

  public:
    /** initialize your data structure here. */
    MinStack(): Stack{}, Min{} {}

    void push(int x)
    {
      Stack.push(x);

      if (Min.empty() || x <= Min.top())
        Min.push(x);
    }

    void pop()
    {
      if (Stack.empty())
        return;

      const int x = Stack.top();
      Stack.pop();

      if (Min.top() == x)
        Min.pop();
    }

    int top()
    {
      return Stack.top();
    }

    int getMin()
    {
      return Min.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

int main()
{
  MinStack* obj = new MinStack();
  obj->push(-2);
  obj->push(0);
  obj->push(-3);
  assert(obj->getMin() == -3);
  obj->pop();
  assert(obj->top() == 0);
  assert(obj->getMin() == -2);
  delete obj;
  return 0;
}
