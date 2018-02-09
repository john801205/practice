#include <algorithm>
#include <iostream>
#include <string>

int main(void)
{
  bool first = true;
  std::string a, b;

  while (std::cin >> a >> b)
  {
    if (not first)
      std::cout << '\n';

    // create a string of max length of a and b
    std::string::size_type len = std::max(a.size(), b.size());
    std::string result (len, 0);

    // add the digit of a from least significant bits
    for (std::string::size_type i = a.size(), j = 0; i-- > 0; j++)
      result[j] += a[i] - '0';

    // add the digit of b from least significant bits
    for (std::string::size_type i = b.size(), j = 0; i-- > 0; j++)
      result[j] += b[i] - '0';

    for (std::string::size_type i = 0; i < result.size(); i++)
    {
      if (result[i] >= 2)
      {
        // f(i) + f(i) = f(i) + f(i-1) + f(i-2) = f(i+1) + f(i-2)
        result[i] -= 2;

        if (i+1 < result.size())
          result[i+1] += 1;
        else
          result += '\1';

        if (i != 0)
        {
          if (i >= 2)
            result[i-2] += 1;
          else
            result[0] += 1;

          // change the index back to the bit just added
          if (i >= 4)
            i = i - 4;
          else
            i = -1;
        }
      }
      else if (result[i] == 1 and i+1 < result.size() and result[i+1] >= 1)
      {
        // f(i) + f(i+1) = f(i+2)
        if (i+2 < result.size())
          result[i+2] += 1;
        else
          result += '\1';

        result[i] -= 1;
        result[i+1] -= 1;
      }
    }

    // reverse the bits
    std::reverse(std::begin(result), std::end(result));

    // formulate as string
    for (auto &c: result)
      c += '0';

    std::cout << result << '\n';
    first = false;
  }

  return 0;
}
