#include <cmath>

#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

class BigIntegerString
{
  private:
    std::string m_digits   = {0};
    bool        m_positive = true;

  public:
    BigIntegerString();
    BigIntegerString(const int);
    BigIntegerString(const unsigned);
    BigIntegerString(const std::string &);

    bool operator==(const BigIntegerString &b) const;
    bool operator>(const BigIntegerString &b) const;

    friend BigIntegerString operator+(const BigIntegerString &,
                                      const BigIntegerString &);
    friend BigIntegerString operator*(const BigIntegerString &,
                                      const BigIntegerString &);

    friend std::ostream &operator<<(std::ostream &, const BigIntegerString &);

  private:
    std::string getString() const;
};

BigIntegerString::BigIntegerString() = default;

BigIntegerString::BigIntegerString(const int integer)
{
  m_positive = (integer >= 0);

  m_digits.clear();
  for (auto i = abs(integer); i != 0; i /= 10)
  {
    m_digits += static_cast<char>(i % 10);
  }
}

BigIntegerString::BigIntegerString(const unsigned integer)
{
  m_positive = true;

  m_digits.clear();
  for (auto i = integer; i != 0; i /= 10)
  {
    m_digits += static_cast<char>(i % 10);
  }
}

static std::string remove_leading_zero(const std::string &a)
{
  for (std::string::size_type i = a.size()-1; i > 0; i--)
    if (a[i] != 0)
      return a.substr(0, i+1);

  return a.substr(0, 1);
}

BigIntegerString::BigIntegerString(const std::string &integer)
{
  if (integer.front() == '-')
  {
    m_positive = false;
    m_digits = integer.substr(1);
  }
  else
  {
    m_positive = true;
    m_digits = integer;
  }

  std::reverse(std::begin(m_digits), std::end(m_digits));

  for (std::string::size_type i = 0; i < m_digits.size(); i++)
    m_digits[i] -= '0';

  m_digits = remove_leading_zero(m_digits);

  // the sign of zero is positive
  if (m_digits.size() == 1 and m_digits[0] == 0)
    m_positive = true;
}

static bool larger(const std::string &a, const std::string &b)
{
  if (a.size() != b.size())
    return a.size() > b.size();

  for (std::string::size_type i = a.size(); i > 0; i--)
    if (a[i] != b[i])
      return a[i] > b[i];

  return a[0] > b[0];
}

bool BigIntegerString::operator==(const BigIntegerString &b) const
{
  return m_positive == b.m_positive and m_digits == b.m_digits;
}

bool BigIntegerString::operator>(const BigIntegerString &b) const
{
  // if the signs of two numbers are not equal,
  // the positive side is bigger
  if (m_positive != b.m_positive)
    return m_positive;

  // check if the digits are larger
  bool result = larger(m_digits, b.m_digits);

  if (m_positive)
    return result;
  else
    return !result;
}

static std::string add(const std::string &a, const std::string &b)
{
  auto length = (a.size() > b.size() ? a.size() : b.size());
  std::string result(length, 0);

  for (std::string::size_type i = 0; i < a.size(); i++)
    result[i] += a[i];

  for (std::string::size_type i = 0; i < b.size(); i++)
    result[i] += b[i];

  char carry = 0;
  for (std::string::size_type i = 0; i < result.size(); i++)
  {
    char digit = result[i] + carry;
    carry = digit / 10;
    result[i] = digit % 10;
  }

  if (carry != 0)
    result += carry;

  return result;
}

static std::string substract(const std::string &a, const std::string &b)
{
  std::string result(a);

  for (std::string::size_type i = 0; i < b.size(); i++)
    result[i] -= b[i];

  char carry = 0;
  for (std::string::size_type i = 0; i < result.size(); i++)
  {
    char digit = result[i] - carry;
    if (digit < 0)
    {
      carry = 1;
      result[i] = digit + 10;
    }
    else
    {
      carry = 0;
      result[i] = digit;
    }
  }

  return remove_leading_zero(result);
}

static std::string multiply(const std::string &a, const char b)
{
  std::string result(a.size(), 0);

  char carry = 0;
  for (std::string::size_type i = 0; i < a.size(); i++)
  {
    result[i] = (a[i] * b + carry) % 10;
    carry     = (a[i] * b + carry) / 10;
  }

  if (carry != 0)
    result += carry;

  return result;
}

static std::string multiply(const std::string &a, const std::string &b)
{
  std::string result(1, 0);
  std::string multiplicand(a);

  for (std::string::size_type i = 0; i < b.size(); i++)
  {
    // for (int j = multiplicand.size() - 1; j >= 0; j--)
    //   std::cerr << static_cast<int>(multiplicand[j]);
    // std::cerr << " * " << static_cast<int>(b[i]) << " = ";

    // std::string multi = multiply(multiplicand, b[i]);
    // for (int j = multi.size() - 1; j >= 0; j--)
    //   std::cerr << static_cast<int>(multi[j]);
    // std::cerr << '\n';

    result = add(result, multiply(multiplicand, b[i]));
    multiplicand = multiply(multiplicand, 10);
  }

  return result;
}

BigIntegerString operator+(const BigIntegerString &a,
                           const BigIntegerString &b)
{
  BigIntegerString result;

  if (a.m_positive == b.m_positive)
  {
    result.m_positive = a.m_positive;
    result.m_digits = add(a.m_digits, b.m_digits);
  }
  else if (a.m_positive)
  {
    // a: +, b: -
    if (larger(a.m_digits, b.m_digits) or a.m_digits == b.m_digits)
    {
      result.m_positive = true;
      result.m_digits = substract(a.m_digits, b.m_digits);
    }
    else
    {
      result.m_positive = false;
      result.m_digits = substract(b.m_digits, a.m_digits);
    }
  }
  else
  {
    // a: -, b: +
    if (larger(b.m_digits, a.m_digits) or b.m_digits == a.m_digits)
    {
      result.m_positive = true;
      result.m_digits = substract(b.m_digits, a.m_digits);
    }
    else
    {
      result.m_positive = false;
      result.m_digits = substract(a.m_digits, b.m_digits);
    }
  }

  return result;
}

BigIntegerString operator*(const BigIntegerString &a,
                           const BigIntegerString &b)
{
  BigIntegerString result;

  if (a.m_digits.size() >= b.m_digits.size())
    result.m_digits = multiply(a.m_digits, b.m_digits);
  else
    result.m_digits = multiply(b.m_digits, a.m_digits);

  // check if result is zero
  if (result.m_digits.size() == 1 and result.m_digits[0] == 0)
    result.m_positive = true;
  else
    result.m_positive = (a.m_positive == b.m_positive);

  return result;
}


std::string BigIntegerString::getString() const
{
  std::string digits = m_digits;
  std::reverse(std::begin(digits), std::end(digits));

  for (std::string::size_type i = 0; i < digits.size(); i++)
    digits[i] += '0';

  if (m_positive)
    return digits;
  else
    return '-' + digits;
}

std::ostream &operator<<(std::ostream &os, const BigIntegerString &integer)
{
  os << integer.getString();
  return os;
}

int main(void)
{
  std::vector<BigIntegerString> tables = {1};
  unsigned N;

  while (std::cin >> N)
  {
    if (N >= tables.size())
    {
      for (unsigned i = tables.size(); i <= N; i++)
      {
        BigIntegerString factorial = tables[i-1] * i;
        tables.push_back(factorial);
      }
    }

    std::cout << N << "!\n"
              << tables[N] << '\n';
  }

  return 0;
}

