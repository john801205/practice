#include <cassert>
#include <iostream>

#define private public
#include "BigPositiveInteger.hpp"
#undef private

int main(void)
{
  // default constructor
  assert(BigPositiveInteger().m_digits == std::vector<BASE_T> ({0}));

  // int constructor
  assert(BigPositiveInteger(0).m_digits == std::vector<BASE_T> ({0U}));
  assert(BigPositiveInteger(1).m_digits == std::vector<BASE_T> ({1U}));

  // unsigned constructor
  assert(BigPositiveInteger(0U).m_digits == std::vector<BASE_T> ({0U}));

  // string constructor
  assert(BigPositiveInteger("0").m_digits == std::vector<BASE_T> ({0U}));
  assert(BigPositiveInteger("1").m_digits == std::vector<BASE_T> ({1U}));
  assert(BigPositiveInteger("255").m_digits == std::vector<BASE_T> ({255U}));

  assert(BigPositiveInteger("000").m_digits == std::vector<BASE_T> ({0U}));
  assert(BigPositiveInteger("99999999980000000001").m_digits == std::vector<BASE_T> ({3136829441U, 1808227880U, 5U}));
  assert(BigPositiveInteger("237684487579686500932345921536").m_digits == std::vector<BASE_T> ({0U, 1U, 2U, 3U}));

  // operator==
  assert(BigPositiveInteger("78") == BigPositiveInteger(78U));
  assert(BigPositiveInteger("0") == BigPositiveInteger(0U));
  assert(!(BigPositiveInteger("1") == BigPositiveInteger(0U)));

  // operator>
  assert(BigPositiveInteger("178") > BigPositiveInteger(78U));
  assert(BigPositiveInteger("178") > BigPositiveInteger(177U));
  assert(!(BigPositiveInteger("8") > BigPositiveInteger(78U)));

  // operator+
  assert(BigPositiveInteger("77") + BigPositiveInteger(1) == BigPositiveInteger(78U));
  assert(BigPositiveInteger("0") + BigPositiveInteger(1) == BigPositiveInteger(1U));
  assert(BigPositiveInteger("123456789000000000") + BigPositiveInteger("87654321000000000") == BigPositiveInteger("211111110000000000"));

  assert(BigPositiveInteger("999999") + BigPositiveInteger(1) == BigPositiveInteger(1000000));

  // operator*
  assert(BigPositiveInteger(1) * BigPositiveInteger(1) == BigPositiveInteger(1U));
  assert(BigPositiveInteger(2) * BigPositiveInteger(1) == BigPositiveInteger(2U));
  assert(BigPositiveInteger(9) * BigPositiveInteger(9) == BigPositiveInteger(81U));
  assert(BigPositiveInteger("9999999999") * BigPositiveInteger("9999999999") == BigPositiveInteger("99999999980000000001"));
  assert(BigPositiveInteger("4294967296") * BigPositiveInteger("4294967296") == BigPositiveInteger("18446744073709551616"));

  return 0;
}
