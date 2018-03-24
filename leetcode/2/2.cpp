#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
  public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
      ListNode *head = nullptr, *previous = nullptr;
      int carry = 0;

      while (l1 != nullptr || l2 != nullptr || carry != 0)
      {
        int val = carry;

        if (l1 != nullptr)
        {
          val += l1->val;
          l1 = l1->next;
        }

        if (l2 != nullptr)
        {
          val += l2->val;
          l2 = l2->next;
        }

        carry = val / 10;
        val = val % 10;

        if (head == nullptr)
        {
          head = new ListNode(val);
          previous = head;
        }
        else
        {
          previous->next = new ListNode(val);
          previous = previous->next;
        }
      }

      return head;
    }
};

int main(void)
{
  return 0;
}
