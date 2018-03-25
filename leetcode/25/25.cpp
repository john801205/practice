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
      last->next = head;

      int size = 0;

      for (ListNode *current = head; current != nullptr; current = current->next)
      {
        size++;
      }

      while (size >= k)
      {
        // reverse the first k node from head
        ListNode *current, *prev;

        prev = last->next;
        current = prev->next;

        for (int i = 1; i < k; i++)
        {
          ListNode *temp = current->next;
          current->next = last->next;
          prev->next = temp;
          last->next = current;

          current = temp;
        }

        last = prev;
        size -= k;
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
  head->next->next->next->next->next = new ListNode(6);
  head->next->next->next->next->next->next = new ListNode(7);

  print(head);

  Solution s;
  print(s.reverseKGroup(head, 3));
  return 0;
}
