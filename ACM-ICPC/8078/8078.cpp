#include <array>
#include <iostream>
#include <string>

int main(void)
{
  std::array<unsigned, 100000> result;
  std::string sequence;
  int N;

  std::cin >> N;
  for (int case_ = 1; case_ <= N; case_++)
  {
    std::cout << "Case " << case_ << ":\n";

    std::cin >> sequence;

    for (std::string::size_type i = sequence.size(); i-- > 0; )
    {
      result[i] = 0;

      if (sequence[i] == ')'
          or sequence[i] == ']'
          or sequence[i] == '}'
          or sequence[i] == '>')
        continue;

      auto index = i+1;
      unsigned count = 0;

      if (index >= sequence.size())
        continue;

      if (result[index] != 0)
      {
        count += result[index];
        index += result[index];
      }

      if (index >= sequence.size())
        continue;

      if ((sequence[i] == '(' and sequence[index] != ')')
          or (sequence[i] == '[' and sequence[index] != ']')
          or (sequence[i] == '{' and sequence[index] != '}')
          or (sequence[i] == '<' and sequence[index] != '>'))
        continue;

      result[i] = count + 2;

      if (index+1 >= sequence.size())
        continue;

      result[i] += result[index+1];
    }

    for (std::string::size_type i = 0; i < sequence.size(); i++)
      std::cout << result[i] << '\n';
  }

  return 0;
}
