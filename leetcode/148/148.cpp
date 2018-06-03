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
    ListNode* sortList(ListNode* head)
    {
      if (head == nullptr)
        return nullptr;

      ListNode small(0), equal(0), big(0);
      int val = head->val;

      while (head != nullptr)
      {
        ListNode *next = head->next;

        if (head->val == val)
        {
          head->next = equal.next;
          equal.next = head;
        }
        else if (head->val > val)
        {
          head->next = big.next;
          big.next = head;
        }
        else
        {
          head->next = small.next;
          small.next = head;
        }

        head = next;
      }

      small.next = sortList(small.next);
      big.next = sortList(big.next);

      ListNode *prev = &small;
      while (prev->next != nullptr)
        prev = prev->next;
      prev->next = equal.next;

      while (prev->next != nullptr)
        prev = prev->next;
      prev->next = big.next;

      return small.next;
    }
};

int main()
{
  return 0;
}
