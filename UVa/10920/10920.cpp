#include <iostream>

int main(void)
{
  long long SZ, P;

  while (std::cin >> SZ >> P) {
    if (SZ == 0 && P == 0)
      break;

    long long pos, size;
    int line, column;

    line = SZ / 2 + 1;
    column = SZ / 2 + 1;

    for (pos = 1, size = 3; size * size <= P; size += 2) {
      line++;
      column++;
      pos = size * size;
    }

    if (pos < P) {
      pos++;
      line++;
    }

    for (int i = 2; i < size && pos < P; i++) {
      pos++;
      column--;
    }

    for (int i = 1; i < size && pos < P; i++) {
      pos++;
      line--;
    }

    for (int i = 1; i < size && pos < P; i++) {
      pos++;
      column++;
    }

    for (int i = 1; i < size && pos < P; i++) {
      pos++;
      line++;
    }

    std::cout << "Line = " << line << ", column = " << column << ".\n";
  }

  return 0;
}
