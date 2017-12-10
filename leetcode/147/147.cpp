#include <iostream>
#include <climits>
using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
  public:
    ListNode* insertionSortList(ListNode* head) {
      ListNode helper(INT_MIN);

      ListNode *current = head;
      while (current != nullptr) {
        ListNode *prev = &helper;

        while (prev->next != nullptr && prev->next->val < current->val)
          prev = prev->next;

        ListNode *next = current->next;
        current->next = prev->next;
        prev->next = current;
        current = next;
      }

      return helper.next;
    }
};

void printList(ListNode *head) {
  ListNode *cur = head;
  while(cur != NULL) {
    cout << cur->val << endl;
    cur = cur->next;
  }
}

int main(void)
{
  ListNode head(10);
  ListNode middle(2);
  ListNode tail(3);
  head.next = &middle;
  middle.next = &tail;

  printList(&head);

  Solution solution;
  printList(solution.insertionSortList(&head));

  return 0;
}
