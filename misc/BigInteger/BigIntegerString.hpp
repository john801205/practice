#ifndef __BIGINTEGERSTRING_H__
#define __BIGINTEGERSTRING_H__

#include <ostream>
#include <string>

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
                                      const unsigned);
    friend BigIntegerString operator+(const BigIntegerString &,
                                      const BigIntegerString &);
    friend BigIntegerString operator-(const BigIntegerString &,
                                      const BigIntegerString &);
    friend BigIntegerString operator*(const BigIntegerString &,
                                      const BigIntegerString &);
    friend BigIntegerString operator/(const BigIntegerString &,
                                      const BigIntegerString &);

    friend std::ostream &operator<<(std::ostream &, const BigIntegerString &);

  private:
    std::string getString() const;
};

#endif
