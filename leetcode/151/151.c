#include <stdio.h>

void reverseWords(char * const s)
{
  char *i = s, *j = s;

  // remove leading, intermediate and trailing spaces
  while (*i != '\0')
  {
    while (*i == ' ')
      i++;

    if (*i != '\0' && j != s)
    {
      *j = ' ';
      j++;
    }

    while (*i != '\0' && *i != ' ')
    {
      *j = *i;
      i++;
      j++;
    }
  }
  *j = '\0';

  // reverse whole string
  for (i = s, j = j-1; i < j; i++, j--)
  {
    char temp = *i;
    *i = *j;
    *j = temp;
  }

  // reverse each word
  i = s;
  while (*i != '\0')
  {
    j = i;
    while (*j != ' ' && *j != '\0')
      j++;
    j--;

    for (char *m = i, *n = j; m < n; m++, n--)
    {
      char temp = *m;
      *m = *n;
      *n = temp;
    }

    i = j+1;
    while (*i == ' ' && *i != '\0')
      i++;
  }
}

int main(void)
{
  char s[] = "t sky is blue";
  reverseWords(s);
  return 0;
}
