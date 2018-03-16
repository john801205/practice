#include <cmath>
#include <iostream>

bool check(int number_of_coconuts, int number_of_people)
{
  for (int i = 0; i < number_of_people; i++)
  {
    if (number_of_coconuts % number_of_people != 1)
      return false;

    number_of_coconuts = (number_of_coconuts-1) - (number_of_coconuts-1)/number_of_people;
  }

  return number_of_coconuts % number_of_people == 0;
}

int main(void)
{
  int number_of_coconuts;

  while (std::cin >> number_of_coconuts && number_of_coconuts >= 0)
  {
    // if (number_of_coconuts == 387420481)
    //   std::cout << number_of_coconuts << " coconuts, 9 people and 1 monkey\n";
    // else if ((number_of_coconuts - 117440505) % 134217728 == 0)
    //   std::cout << number_of_coconuts << " coconuts, 8 people and 1 monkey\n";
    // else if ((number_of_coconuts - 823537) % 5764801 == 0)
    //   std::cout << number_of_coconuts << " coconuts, 7 people and 1 monkey\n";
    // else if ((number_of_coconuts - 233275) % 279936 == 0)
    //   std::cout << number_of_coconuts << " coconuts, 6 people and 1 monkey\n";
    // else if ((number_of_coconuts - 3121) % 15625 == 0)
    //   std::cout << number_of_coconuts << " coconuts, 5 people and 1 monkey\n";
    // else if ((number_of_coconuts - 765) % 1024 == 0)
    //   std::cout << number_of_coconuts << " coconuts, 4 people and 1 monkey\n";
    // else if ((number_of_coconuts - 25) % 81 == 0)
    //   std::cout << number_of_coconuts << " coconuts, 3 people and 1 monkey\n";
    // else if ((number_of_coconuts - 3) % 8 == 0)
    //   std::cout << number_of_coconuts << " coconuts, 2 people and 1 monkey\n";
    // else
    //   std::cout << number_of_coconuts << " coconuts, no solution\n";

    bool success = false;
    int number_of_people;

    for (number_of_people = sqrt(number_of_coconuts)+1;
         number_of_people >= 2;
         number_of_people--)
    {
      if (check(number_of_coconuts, number_of_people))
      {
        success = true;
        break;
      }
    }

    if (!success)
      std::cout << number_of_coconuts << " coconuts, no solution\n";
    else
      std::cout << number_of_coconuts << " coconuts, "
                << number_of_people   << " people and 1 monkey\n";
  }

  return 0;
}
