#include <regex>
#include <iostream>

#include "BigPositiveInteger.hpp"

static std::vector<BASE_T>
remove_leading_zero(const std::vector<BASE_T> &integer);

BigPositiveInteger::BigPositiveInteger() = default;

BigPositiveInteger::BigPositiveInteger(const int integer)
{
  // TODO exception
  if (integer < 0)
    throw __LINE__;

  if (integer == 0)
    return;

  m_digits.clear();
  for (auto i = integer; i != 0; i /= m_base)
  {
    m_digits.emplace_back(i % m_base);
  }
}

BigPositiveInteger::BigPositiveInteger(const unsigned integer)
{
  if (integer == 0)
    return;

  m_digits.clear();
  for (auto i = integer; i != 0; i /= m_base)
  {
    m_digits.emplace_back(i % m_base);
  }
}

BigPositiveInteger::BigPositiveInteger(const std::string &integer)
{
  // TODO exception
  static const std::regex int_regex ("\\d+");
  if (not std::regex_match(integer, int_regex))
    throw __LINE__;

  if (integer == "0")
    return;

  BigPositiveInteger result (0);

  for (std::string::size_type i = 0; i < integer.size(); i++)
    result = result * 10 + (integer[i] - '0');

  m_digits = result.m_digits;
}

bool BigPositiveInteger::operator==(const BigPositiveInteger &b) const
{
  return m_digits == b.m_digits;
}

bool BigPositiveInteger::operator>(const BigPositiveInteger &b) const
{
  if (m_digits.size() != b.m_digits.size())
    return m_digits.size() > b.m_digits.size();

  for (std::vector<BASE_T>::size_type i = m_digits.size(); i-- > 0; )
    if (m_digits[i] != b.m_digits[i])
      return m_digits[i] > b.m_digits[i];

  return false;
}

BigPositiveInteger operator+(const BigPositiveInteger &a,
                             const BigPositiveInteger &b)
{
  // copy the larger one to the result
  BigPositiveInteger result = (a > b ? a: b);

  // determine the size of smaller one and larger one
  auto smaller_size = a.m_digits.size(),
       larger_size  = b.m_digits.size();

  if (smaller_size > larger_size)
    std::swap(smaller_size, larger_size);

  // carry bit
  MAX_T carry = 0;

  // for each index [0, smaller_size), we add each base and set the carry bit
  for (std::vector<BASE_T>::size_type i = 0; i < smaller_size; i++)
  {
    MAX_T digit = a.m_digits[i];
    digit += b.m_digits[i];
    digit += carry;

    // std::cerr << a.m_digits[i] << " + " << b.m_digits[i] << " + " << carry << " = " << digit << '\n';

    result.m_digits[i] = digit % result.m_base;
    carry = digit / result.m_base;
  }

  // for each index [smaller_size, larger_size),
  // we add and set the carry bit
  for (std::vector<BASE_T>::size_type i = smaller_size;
       i < larger_size and carry != 0;
       i++)
  {
    MAX_T digit = result.m_digits[i];
    digit += carry;

    result.m_digits[i] = digit % result.m_base;
    carry = digit / result.m_base;
  }

  // add the carry bit
  while (carry != 0)
  {
    result.m_digits.emplace_back(carry % result.m_base);
    carry = carry / result.m_base;
  }

  return result;
}

BigPositiveInteger operator*(const BigPositiveInteger &a,
                             const BigPositiveInteger &b)
{
  // determine the maximum size of result
  auto length = a.m_digits.size() + b.m_digits.size();

  // result instance
  BigPositiveInteger result;
  result.m_digits = std::vector<BASE_T> (length, 0);

  // for each base of b, we use it to multiply a
  for (std::vector<BASE_T>::size_type j = 0; j < b.m_digits.size(); j++)
  {
    MAX_T carry = 0;

    for (std::vector<BASE_T>::size_type i = 0; i < a.m_digits.size(); i++)
    {
      MAX_T digit = a.m_digits[i];
      digit *= b.m_digits[j];
      digit += result.m_digits[i+j];
      digit += carry;
      // std::cerr << __LINE__ << ' '  << a.m_digits[i] << '*' << b.m_digits[j] << ": " << digit << '\n';
      // std::cerr << __LINE__ << ' '  << result.m_digits[i+j] << ' ' << carry << '\n';

      result.m_digits[i+j] = digit % result.m_base;
      carry = digit / result.m_base;
    }

    for (auto i = a.m_digits.size(); i < result.m_digits.size() and carry != 0; i++)
    {
      MAX_T digit = result.m_digits[i+j];
      digit += carry;
      // std::cerr << result.m_digits[i+j] << ' ' << carry << ": " << digit << '\n';

      result.m_digits[i+j] = digit % result.m_base;
      carry = digit / result.m_base;
    }
  }

  result.m_digits = remove_leading_zero(result.m_digits);

  return result;
}

static std::vector<BASE_T>
remove_leading_zero(const std::vector<BASE_T> &integer)
{
  auto first = std::begin(integer);

  for (auto i = integer.size()-1; i > 0; i--)
  {
    if (integer[i] != 0)
    {
      return std::vector<BASE_T> (first, first+i+1);
    }
  }

  return std::vector<BASE_T> (first, first+1);
}
