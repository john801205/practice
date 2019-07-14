
struct ListNode
{
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

class Solution
{
  public:
    ListNode *detectCycle(ListNode *head)
    {
      ListNode *slow = head, *fast = head;

      while (true)
      {
        if (slow == nullptr)
          return nullptr;
        slow = slow->next;

        if (fast == nullptr || fast->next == nullptr)
          return nullptr;
        fast = fast->next->next;

        if (slow == fast)
          break;
      }

      slow = head;
      while (slow != fast)
      {
        slow = slow->next;
        fast = fast->next;
      }

      return slow;
    }
};

int main()
{
  return 0;
}
