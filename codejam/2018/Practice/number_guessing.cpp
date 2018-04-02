#include <iostream>
#include <string>

int main(void)
{
  int t;

  std::cin >> t;
  for (int i = 0; i < t; i++)
  {
    int a, b, n;

    std::cin >> a >> b >> n;
    a++;

    while (a <= b)
    {
      std::string result;
      int middle = (a+b) / 2;

      std::cout << middle << '\n';
      std::cin >> result;

      if (result == "CORRECT")
      {
        break;
      }
      else if (result == "TOO_SMALL")
      {
        a = middle+1;
      }
      else if (result == "TOO_BIG")
      {
        b = middle-1;
      }
      else
      {
        return 0;
      }
    }
  }

  return 0;
}
