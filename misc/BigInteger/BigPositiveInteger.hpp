#ifndef __BIGPOSITIVEINTEGER_H__
#define __BIGPOSITIVEINTEGER_H__

#include <limits>
#include <string>
#include <vector>

#define BASE_T uint32_t
#define MAX_T  uint64_t

class BigPositiveInteger
{
  private:
    std::vector<BASE_T> m_digits = {0};
    MAX_T               m_base   = std::numeric_limits<BASE_T>::max() + 1UL;

  public:
    BigPositiveInteger();
    BigPositiveInteger(const int);
    BigPositiveInteger(const unsigned);
    BigPositiveInteger(const std::string &);

    bool operator==(const BigPositiveInteger &) const;
    bool operator>(const BigPositiveInteger &) const;

    friend BigPositiveInteger operator+(const BigPositiveInteger &,
                                         const BigPositiveInteger &);
    friend BigPositiveInteger operator*(const BigPositiveInteger &,
                                        const BigPositiveInteger &);
};

#endif
