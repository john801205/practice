#include <iostream>
#include <vector>

class Solution
{
  public:
    void rotate(std::vector<std::vector<int>> &matrix)
    {
      const std::vector<int>::size_type n = matrix.size();

      for (std::vector<std::vector<int>>::size_type i = 0; i < n/2; i++)
      {
        for (std::vector<int>::size_type j = i; j < n-1-i; j++)
        {
          int temp = matrix[i][j];

          matrix[i][j] = matrix[n-1-j][i];
          matrix[n-1-j][i] = matrix[n-1-i][n-1-j];
          matrix[n-1-i][n-1-j] = matrix[j][n-1-i];
          matrix[j][n-1-i] = temp;
        }
      }
    }
};

void print(const std::vector<std::vector<int>> &matrix)
{
  for (const auto &row: matrix)
  {
    for (const auto &element: row)
    {
      std::cout << element << ' ';
    }
    std::cout << '\n';
  }
}

int main(void)
{
  std::vector<std::vector<int>> matrix = {{1, 2}, {3, 4}};
  Solution s;

  print(matrix);
  s.rotate(matrix);
  print(matrix);
  return 0;
}
