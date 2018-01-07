#include <climits>

#include <iostream>
#include <map>
#include <vector>

std::map<unsigned, unsigned> build_fibonacci_map(void)
{
  std::map<unsigned, unsigned> fibonacci;
  fibonacci[1] = 0;
  fibonacci[2] = 1;

  unsigned index = 2;
  unsigned v1 = 1, v2 = 2, v3 = 3;
  while (v3 < INT_MAX)
  {
    fibonacci[v3] = index;

    v1 = v2;
    v2 = v3;
    v3 = v1+v2;
    index++;
  }

  return fibonacci;
}

bool is_upper_character(const char c)
{
  return c >= 'A' && c <= 'Z';
}

std::string decrypht(const std::map<unsigned, unsigned> &fibonacci,
                     const std::string                  &ciphertext,
                     const std::vector<unsigned>        &keys)
{
  std::string plaintext;
  std::string::size_type pos = 0;

  for (const auto &key: keys)
  {
    while (pos < ciphertext.length()
           && !is_upper_character(ciphertext[pos]))
      pos++;

    // reach the end of ciphertext, terminate the decryption
    if (pos == ciphertext.length())
      break;

    unsigned new_pos = fibonacci.at(key);
    if (new_pos >= plaintext.length())
      plaintext.resize(new_pos+1, ' ');

    plaintext[new_pos] = ciphertext[pos];
    pos++;
  }

  return plaintext;
}

int main(void)
{
  int number_of_test_cases;
  std::map<unsigned, unsigned> fibonacci = build_fibonacci_map();

  while (std::cin >> number_of_test_cases)
  {
    for (int case_ = 0; case_ < number_of_test_cases; case_++)
    {
      int number_of_keys;
      std::cin >> number_of_keys;

      std::vector<unsigned> keys (number_of_keys);
      std::string ciphertext;

      for (int i = 0; i < number_of_keys; i++)
        std::cin >> keys[i];

      // discard the remaining line after fibonacci numbers
      std::getline(std::cin, ciphertext);
      std::getline(std::cin, ciphertext);

      std::cout << decrypht(fibonacci, ciphertext, keys) << '\n';
    }
  }

  return 0;
}
