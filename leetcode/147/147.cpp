#include <iostream>
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
      ListNode *current;

      current = head;
      head = nullptr;

      while (current != nullptr) {
        ListNode *next = current->next;
        ListNode *ptr = head;
        ListNode *prev = nullptr;

        while (ptr != nullptr && ptr->val < current->val) {
          prev = ptr;
          ptr = ptr->next;
        }

        if (prev == nullptr) {
          head = current;
          current->next = ptr;
        } else {
          current->next = ptr;
          prev->next = current;
        }

        current = next;
      }

      return head;
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

  printList(&head);

  Solution solution;
  printList(solution.insertionSortList(nullptr));

  return 0;
}
