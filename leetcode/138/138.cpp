#include <unordered_map>

class Node
{
  public:
    int val;
    Node* next;
    Node* random;

    Node() {}

    Node(int _val, Node* _next, Node* _random)
    {
      val = _val;
      next = _next;
      random = _random;
    }
};

class Solution
{
  public:
    Node* copyRandomList(Node* head)
    {
      Node result(0, nullptr, nullptr);
      Node *tail = &result;
      std::unordered_map<Node*, Node*> inverted;

      while (head != nullptr)
      {
        Node *current = new Node(head->val, nullptr, head->random);
        inverted[head] = current;
        tail->next = current;
        tail = current;
        head = head->next;
      }

      head = result.next;
      while (head != nullptr)
      {
        if (head->random != nullptr)
          head->random = inverted[head->random];

        head = head->next;
      }

      return result.next;
    }
};

int main()
{
  return 0;
}
