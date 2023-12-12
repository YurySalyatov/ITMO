#include <string_view>

#include <climits>
#include <cstring>
#include <iostream>

using namespace std;

class LN
{
	bool NaN = false;
	char sign = '+';
	char *number = (char *)calloc(1, sizeof(char));
	int len = 0;

  public:
	explicit LN(long long int a = 0);
	explicit LN(const char *digits);
	explicit LN(string string_number);
	explicit LN(string_view string_number);
	LN(const LN &other);
	LN(LN &&other) noexcept;
	~LN();
	LN &operator=(const LN &other);
	LN &operator=(LN &&other) noexcept;
	LN operator+(const LN &other) const;
	LN operator-() const;
	LN operator-(const LN &other) const;
	LN operator*(const LN &other) const;
	LN operator/(const LN &other) const;
	LN operator%(const LN &other) const;
	LN sqrt() const;
	void operator+=(const LN &other);
	void operator-=(const LN &other);
	void operator*=(const LN &other);
	void operator/=(const LN &other);
	void operator%=(const LN &other);
	bool operator>(const LN &other) const noexcept;
	bool operator==(const LN &other) const noexcept;
	bool operator<(const LN &other) const noexcept;
	bool operator<=(const LN &other) const noexcept;
	bool operator>=(const LN &other) const noexcept;
	bool operator!=(const LN &other) const noexcept;
	bool isNaN() const;
	int length() const;
	char getSign() const;
	char *getNumber() const;
	friend ostream &operator<<(ostream &out, const LN &that);
	explicit operator long long() const;
	explicit operator bool() const;
};
LN operator"" _ln(const char *str);
