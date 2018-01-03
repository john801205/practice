#include <iostream>

int main(void)
{
  unsigned long long tables[30001] = {0};
  unsigned int coins[] = {1, 5, 10, 25, 50};

  tables[0] = 1;
  for (unsigned i = 0; i < 5; i++) {
    for (unsigned int j = coins[i]; j <= 30000; j++) {
      tables[j] += tables[j - coins[i]];
    }
  }

  int number;
  while (std::cin >> number) {
    if (tables[number] == 1)
      std::cout << "There is only 1 way to produce " << number << " cents change." << std::endl;
    else
      std::cout << "There are " << tables[number] << " ways to produce " << number << " cents change." << std::endl;
  }

  return 0;
}
