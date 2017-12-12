#include <iostream>

char **make_2d_array(int N)
{
  char **array = new char*[N];
  for (int i = 0; i < N; i++)
    array[i] = new char[N];

  return array;
}

void free_2d_array(char **array, int N)
{
  for (int i = 0; i < N; i++)
    delete[] array[i];

  delete[] array;
}

bool match(char **square, char **target, int n, int row, int col, int degree)
{
  if (degree == 0) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (square[row+i][col+j] != target[i][j])
          return false;
      }
    }
  } else if (degree == 90) {
    for (int i = 0, k = 0; i < n; i++, k++) {
      for (int j = 0, l = n-1; j < n; j++, l--) {
        if (square[row+i][col+j] != target[l][k])
          return false;
      }
    }
  } else if (degree == 180) {
    for (int i = 0, k = n-1; i < n; i++, k--) {
      for (int j = 0, l = n-1; j < n; j++, l--) {
        if (square[row+i][col+j] != target[k][l])
          return false;
      }
    }
  } else {
    for (int i = 0, k = n-1; i < n; i++, k--) {
      for (int j = 0, l = 0; j < n; j++, l++) {
        if (square[row+i][col+j] != target[l][k])
          return false;
      }
    }
  }

  return true;
}

int count(char **square, char **target, int N, int n, int degree)
{
  int count = 0;
  for (int i = 0; i <= N - n; i++) {
    for (int j = 0; j <= N - n; j++) {
      if (match(square, target, n, i, j, degree) == true)
        ++count;
    }
  }

  return count;
}

int main(void)
{
  int N, n;

  while (std::cin >> N >> n) {
    if (N == 0 && n == 0)
      break;

    char **square, **target;
    square = make_2d_array(N);
    target = make_2d_array(n);

    for(int i = 0; i < N; i++)
      for(int j = 0; j < N; j++)
        std::cin >> square[i][j];

    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++)
        std::cin >> target[i][j];

    std::cout << count(square, target, N, n, 0) << ' '
              << count(square, target, N, n, 90) << ' '
              << count(square, target, N, n, 180) << ' '
              << count(square, target, N, n, 270) << std::endl;;

    free_2d_array(square, N);
    free_2d_array(target, n);
  }

  return 0;
}
