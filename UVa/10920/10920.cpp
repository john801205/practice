#include <iostream>
#include <algorithm>
#include <cmath>

int main(void)
{
  unsigned long long SZ, P;

  while (std::cin >> SZ >> P) {
    if (SZ == 0 && P == 0)
      break;

    unsigned long long pos, size;
    unsigned long long line, column;

    size = (unsigned long long)std::sqrt(P);
    if ((size & 1) == 0)
      size--;

    line = SZ / 2 + 1 + (size - 1) / 2;
    column = SZ / 2 + 1 + (size - 1) / 2;
    pos = size * size;

    size += 2;

    if (pos < P) {
      line++;
      column -= std::min(P - pos, size - 1) - 1; // 1 is already added to line
      pos += std::min(P - pos, size - 1);
    }

    if (pos < P) {
      line -= std::min(P - pos, size - 1);
      pos += std::min(P - pos, size - 1);
    }

    if (pos < P) {
      column += std::min(P - pos, size - 1);
      pos += std::min(P - pos, size - 1);
    }

    if (pos < P) {
      line += std::min(P - pos, size - 1);
      pos += std::min(P - pos, size - 1);
    }

    std::cout << "Line = " << line << ", column = " << column << ".\n";
  }

  return 0;
}
