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
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
      ListNode *prev = nullptr, *cur = head, *end = head;

      for (int i = 1; i < n; i++)
        end = end->next;

      while (end->next != nullptr)
      {
        end = end->next;
        prev = cur;
        cur = cur->next;
      }

      if (prev == nullptr)
        return cur->next;

      prev->next = cur->next;
      return head;
    }
};

int main()
{
  return 0;
}
