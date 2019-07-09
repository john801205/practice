
struct ListNode
{
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

class Solution
{
  public:
    ListNode* swapPairs(ListNode* head)
    {
      ListNode temp(0);
      temp.next = head;

      ListNode *cur = &temp;
      while (cur != nullptr)
      {
        ListNode *first = cur->next;
        if (first == nullptr)
          break;

        ListNode *second = first->next;
        if (second == nullptr)
          break;

        first->next = second->next;
        second->next = first;
        cur->next = second;

        cur = first;
      }

      return temp.next;
    }
};

int main()
{
  return 0;
}
