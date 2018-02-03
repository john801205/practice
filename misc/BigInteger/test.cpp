#include <cassert>

#define private public
#include "BigIntegerString.hpp"
#undef private

int main(void)
{
  // default constructor
  assert(BigIntegerString().m_digits == std::string ({0}));
  assert(BigIntegerString().m_positive == true);

  // int constructor
  assert(BigIntegerString(1).m_digits == std::string ({1}));
  assert(BigIntegerString(1).m_positive == true);

  assert(BigIntegerString(123).m_digits == std::string ({3, 2, 1}));
  assert(BigIntegerString(123).m_positive == true);

  assert(BigIntegerString(-1).m_digits == std::string ({1}));
  assert(BigIntegerString(-1).m_positive == false);

  assert(BigIntegerString(-123).m_digits == std::string ({3, 2, 1}));
  assert(BigIntegerString(-123).m_positive == false);

  // unsigned constructor
  assert(BigIntegerString(1U).m_digits == std::string ({1}));
  assert(BigIntegerString(1U).m_positive == true);

  assert(BigIntegerString(123U).m_digits == std::string ({3, 2, 1}));
  assert(BigIntegerString(123U).m_positive == true);

  // std::string constructor
  assert(BigIntegerString("4567").m_digits == std::string ({7, 6, 5, 4}));
  assert(BigIntegerString("4567").m_positive == true);

  assert(BigIntegerString("004567").m_digits == std::string ({7, 6, 5, 4}));
  assert(BigIntegerString("004567").m_positive == true);

  assert(BigIntegerString("-4567").m_digits == std::string ({7, 6, 5, 4}));
  assert(BigIntegerString("-4567").m_positive == false);

  assert(BigIntegerString("-004567").m_digits == std::string ({7, 6, 5, 4}));
  assert(BigIntegerString("-004567").m_positive == false);

  assert(BigIntegerString("0").m_digits == std::string ({0}));
  assert(BigIntegerString("0").m_positive == true);

  assert(BigIntegerString("000").m_digits == std::string ({0}));
  assert(BigIntegerString("000").m_positive == true);

  assert(BigIntegerString("-0").m_digits == std::string ({0}));
  assert(BigIntegerString("-0").m_positive == true);

  assert(BigIntegerString("-000").m_digits == std::string ({0}));
  assert(BigIntegerString("-000").m_positive == true);

  // operator==
  assert(BigIntegerString("4567") == BigIntegerString("4567"));
  assert(BigIntegerString("0") == BigIntegerString("0"));
  assert(BigIntegerString("-0") == BigIntegerString("0"));

  assert(!(BigIntegerString("123") == BigIntegerString("4567")));
  assert(!(BigIntegerString("-4567") == BigIntegerString("4567")));

  // operator>
  assert(BigIntegerString("4567") > BigIntegerString("123"));
  assert(!(BigIntegerString("123") > BigIntegerString("4567")));

  assert(BigIntegerString("4567") > BigIntegerString("-123"));
  assert(!(BigIntegerString("-4567") > BigIntegerString("123")));

  assert(BigIntegerString("-1") > BigIntegerString("-123"));
  assert(!(BigIntegerString("-4567") > BigIntegerString("-123")));

  // operator+
  assert(BigIntegerString("4567") + BigIntegerString("123") == BigIntegerString("4690"));
  assert(BigIntegerString("1111") + BigIntegerString("8889") == BigIntegerString("10000"));
  assert(BigIntegerString("-4567") + BigIntegerString("-123") == BigIntegerString("-4690"));

  assert(BigIntegerString("4567") + BigIntegerString("-123") == BigIntegerString("4444"));
  assert(BigIntegerString("67") + BigIntegerString("-123") == BigIntegerString("-56"));
  assert(BigIntegerString("-123") + BigIntegerString("4567") == BigIntegerString("4444"));
  assert(BigIntegerString("-123") + BigIntegerString("45") == BigIntegerString("-78"));

  assert(BigIntegerString("1000") + BigIntegerString("-1") == BigIntegerString("999"));
  assert(BigIntegerString("1000") + BigIntegerString("-991") == BigIntegerString("9"));
  assert(BigIntegerString("1") + BigIntegerString("-1") == BigIntegerString("0"));

  // operator-
  assert(BigIntegerString("923") - BigIntegerString("-123") == BigIntegerString("1046"));
  assert(BigIntegerString("-923") - BigIntegerString("123") == BigIntegerString("-1046"));

  assert(BigIntegerString("923") - BigIntegerString("123") == BigIntegerString("800"));
  assert(BigIntegerString("923") - BigIntegerString("1234") == BigIntegerString("-311"));
  assert(BigIntegerString("-923") - BigIntegerString("-123") == BigIntegerString("-800"));
  assert(BigIntegerString("-923") - BigIntegerString("-1234") == BigIntegerString("311"));

  assert(BigIntegerString("-1") - BigIntegerString("-1") == BigIntegerString("0"));

  return 0;
}
