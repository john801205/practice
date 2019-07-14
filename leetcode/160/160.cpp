struct ListNode
{
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

class Solution
{
  public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
      ListNode *currentA = headA, *currentB = headB;

      while (currentA != nullptr || currentB != nullptr)
      {
        if (currentA == currentB)
          return currentA;

        if (currentA == nullptr)
          currentA = headB;
        else
          currentA = currentA->next;

        if (currentB == nullptr)
          currentB = headA;
        else
          currentB = currentB->next;
      }

      return nullptr;
    }
};

int main()
{
  return 0;
}
