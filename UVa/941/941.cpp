#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main(void)
{
  int number_of_samples;

  while (std::cin >> number_of_samples)
  {
    for (int sample = 0; sample < number_of_samples; sample++)
    {
      std::string S;
      unsigned long long N;

      std::cin >> S >> N;

      // build factorial array: factorial[i] = i!
      std::vector<unsigned long long> factorial (S.length() + 1, 1);
      for (std::vector<unsigned long long>::size_type i = 1; i < factorial.size(); i++)
        factorial[i] = factorial[i-1] * i;

      // sort the string
      std::sort(S.begin(), S.end());

      std::string result;
      while (S.length() != 0)
      {
        unsigned index = N / factorial[S.length()-1];
        if (index >= S.length()) // When S.length() == 2 and N == 2
          index = S.length() - 1;

        result += S[index];

        N %= factorial[S.length()-1];
        S.erase(index, 1);
      }

      std::cout << result << '\n';
    }
  }

  return 0;
}
