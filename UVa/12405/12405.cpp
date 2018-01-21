#include <iostream>
#include <string>

int main(void)
{
  int number_of_test_cases;

  while (std::cin >> number_of_test_cases)
  {
    for (int case_ = 1; case_ <= number_of_test_cases; case_++)
    {
      int number_of_fields;
      std::string fields;

      std::cin >> number_of_fields;
      std::cin.ignore();
      std::getline(std::cin, fields);

      int number_of_scarecrow = 0;

      for (int i = 0; i < number_of_fields; i++)
      {
        if (fields[i] == '.')
        {
          // put the scarecrow on the next field
          // and we can skip the next two fields
          number_of_scarecrow++;
          i+=2;
        }
      }

      std::cout << "Case " << case_ << ": " << number_of_scarecrow << '\n';
    }
  }

  return 0;
}
