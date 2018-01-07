#include <climits>

#include <iostream>
#include <vector>

std::vector<unsigned> build_fibonacci(void)
{
  std::vector<unsigned> fibonacci = {1, 2};
  unsigned pre = 2, cur = 3;

  while (cur < INT_MAX)
  {
    fibonacci.push_back(cur);

    auto temp = pre;
    pre = cur;
    cur = cur + temp;
  }

  return fibonacci;
}

std::vector<unsigned>::size_type binary_search(const std::vector<unsigned> &fibonacci,
                                               unsigned value)
{
  std::vector<unsigned>::size_type left = 0,
                                   right = fibonacci.size() - 1;

  while (left <= right) {
    std::vector<unsigned>::size_type middle = (left+right) / 2;

    if (fibonacci[middle] == value)
      return middle;
    else if (fibonacci[middle] > value)
      right = middle - 1;
    else
      left = middle + 1;
  }

  return fibonacci.size();
}

bool is_upper_character(const char c)
{
  return c >= 'A' && c <= 'Z';
}

std::string decrypht(const std::vector<unsigned> &fibonacci,
                     const std::string           &ciphertext,
                     const std::vector<unsigned> &keys)
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

    auto new_pos = binary_search(fibonacci, key);
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
  std::vector<unsigned> fibonacci = build_fibonacci();

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
