struct ListNode
{
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

class Solution
{
  public:
    ListNode* reverseBetween(ListNode* head, int m, int n)
    {
      ListNode dummy(0);
      dummy.next = head;

      ListNode *pre = &dummy;
      for (int i = 0; i < m-1; i++)
        pre = pre->next;

      ListNode *cur = pre->next;
      ListNode *next = cur->next;

      for (int i = 0; i < n - m; i++)
      {
        cur->next = next->next;
        next->next = pre->next;
        pre->next = next;
        next = cur->next;
      }

      return dummy.next;
    }
};

int main()
{
  return 0;
}
