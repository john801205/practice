#include <iostream>

#define MAX_TIME 1000000

int main(void)
{
  int n, m;

  while (std::cin >> n >> m) {
    if (n == 0 && m == 0)
      break;

    bool time[MAX_TIME], conflict;

    conflict = false;
    for (int i = 0; i < MAX_TIME; i++)
      time[i] = false;

    for (int i = 0; i < n; i++) {
      int start, end;
      std::cin >> start >> end;

      for (int t = start; !conflict && t < end; t++) {
        if (time[t])
          conflict = true;
        else
          time[t] = true;
      }
    }

    for (int i = 0; i < m; i++) {
      int start, end, interval;
      std::cin >> start >> end >> interval;

      for (int repeat = 0; !conflict && repeat+start < MAX_TIME; repeat+=interval) {
        for (int t = start; !conflict && t < end && repeat+t < MAX_TIME; t++) {
          if (time[repeat+t])
            conflict = true;
          else
            time[repeat+t] = true;
        }
      }
    }

    std::cout << (conflict ? "CONFLICT": "NO CONFLICT") << std::endl;
  }

  return 0;
}
