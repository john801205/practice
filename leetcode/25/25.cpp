#include <iostream>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
  public:
    ListNode* reverseKGroup(ListNode* head, int k)
    {
      ListNode result = ListNode(0);
      ListNode *last  = &result;

      while (head != nullptr)
      {
        ListNode *current, *prev;
        int size = 0;

        // check if the remaining size is larger than or equal to k
        current = head;
        for (size = 0; size < k; size++)
        {
          if (current == nullptr)
          {
            break;
          }

          current = current->next;
        }

        if (size != k)
        {
          last->next = head;
          break;
        }

        // reverse the first k node from head
        prev = nullptr;
        current = head;

        for (int i = 0; i < k; i++)
        {
          ListNode *next = current->next;
          current->next = prev;
          prev = current;
          current = next;
        }

        last->next = prev;
        last = head;
        head = current;
      }

      return result.next;
    }
};

void print(ListNode *head)
{
  while (head != nullptr)
  {
    std::cerr << head->val << ' ';
    head = head->next;
  }
  std::cerr << '\n';
}

int main(void)
{
  ListNode *head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(3);
  head->next->next->next = new ListNode(4);
  head->next->next->next->next = new ListNode(5);

  print(head);

  Solution s;
  print(s.reverseKGroup(head, 2));
  return 0;
}
