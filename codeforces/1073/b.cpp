#include <cstdio>

#include <vector>

int main()
{
  int number_of_books;
  scanf("%d", &number_of_books);

  std::vector<int> stacks(number_of_books);
  std::vector<bool> removed(number_of_books+1, false);

  for (int i = 0; i < number_of_books; i++)
  {
    scanf("%d", &stacks[i]);
  }

  for (int i = 0, offset = 0; i < number_of_books; i++)
  {
    int book;
    scanf("%d", &book);

    if (removed[book])
    {
      printf("0 ");
      continue;
    }

    int count = 0;
    while (true)
    {
      count += 1;
      removed[stacks[offset]] = true;
      if (stacks[offset] == book)
        break;

      offset += 1;
    }

    offset += 1;
    printf("%d ", count);
  }

  return 0;
}
