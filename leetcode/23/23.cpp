#include <iostream>
#include <queue>
#include <vector>

struct ListNode
{
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

struct QueueNode
{
  int val;
  ListNode *next;

  QueueNode(int val, ListNode *next): val(val), next(next) {}

  friend bool operator>(const QueueNode &lhs, const QueueNode &rhs)
  {
    return lhs.val > rhs.val;
  }
};

class Solution
{
  public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists)
    {
      ListNode *head = new ListNode(0);
      ListNode *prev = head;

      std::priority_queue<QueueNode,
                          std::vector<QueueNode>,
                          std::greater<QueueNode>> priority_queue;

      for (std::vector<ListNode *>::size_type i = 0; i < lists.size(); i++)
      {
        if (lists[i] != nullptr)
        {
          priority_queue.emplace(lists[i]->val, lists[i]->next);
        }
      }

      while (!priority_queue.empty())
      {
        QueueNode top = priority_queue.top();
        priority_queue.pop();

        prev->next = new ListNode(top.val);
        prev = prev->next;

        if (top.next != nullptr)
        {
          priority_queue.emplace(top.next->val, top.next->next);
        }
      }

      ListNode *temp = head;
      head = head->next;
      free(temp);

      return head;
    }
};

int main(void)
{
  return 0;
}
