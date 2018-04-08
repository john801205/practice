#include <iostream>
#include <vector>

class Solution
{
  public:
    void setZeroes(std::vector<std::vector<int>>& matrix)
    {
      int col0 = 1;

      for (std::vector<std::vector<int>>::size_type i = 0; i < matrix.size(); i++)
      {
        if (matrix[i][0] == 0)
        {
          col0 = 0;
        }

        for (std::vector<int>::size_type j = 1; j < matrix[i].size(); j++)
        {
          if (matrix[i][j] == 0)
          {
            matrix[0][j] = 0;
            matrix[i][0] = 0;
          }
        }
      }

      for (std::vector<std::vector<int>>::size_type i = matrix.size(); i-- > 0; )
      {
        for (std::vector<int>::size_type j = matrix[i].size(); j-- > 1; )
        {
          if (matrix[i][0] == 0 || matrix[0][j] == 0)
          {
            matrix[i][j] = 0;
          }
        }

        if (col0 == 0)
        {
          matrix[i][0] = 0;
        }
      }
    }
};

int main(void)
{
  return 0;
}
