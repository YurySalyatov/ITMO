#include "LN.h"

LN::LN(long long int a)
{
	NaN = false;
	if (a == 0)
	{
		len = 1;
		free(number);
		number = (char *)calloc(1, sizeof(char));

		if (number == nullptr)
		{
			throw "Memory allocation error";
		}
		sign = '+';
		number[0] = '0';
	}
	else
	{
		long long int y = a;
		if (y == LONG_LONG_MIN)
		{
			len = 10;
			number = (char *)calloc(19, sizeof(char));
			for (int i = 0; i < 19; i++, y /= 10)
			{
				number[i] = (-(y % 10)) + '0';
			}
			sign = '-';
		}
		else
		{
			int shift = 1;
			sign = '+';
			if (y < 0)
			{
				shift = -1;
				sign = '-';
			}
			while (y > 0)
			{
				len++;
				y /= 10;
			}

			free(number);
			number = (char *)calloc(len, sizeof(char));

			if (number == nullptr)
			{
				throw "Memory allocation error";
			}

			int i = 0;
			while (a > 0)
			{
				number[i++] = (a % 10) + '0';
				a /= 10;
			}
		}
	}
}

LN::LN(const char *digits)
{
	if (strlen(digits) == 3 && digits[0] == 'N' && digits[1] == 'a' && digits[2] == 'N')
	{
		NaN = true;
		free(number);
		number = (char *)calloc(1, sizeof(char));

		if (number == nullptr)
		{
			throw "Memory allocation error";
		}
		number[0] = 0;
		return;
	}
	len = strlen(digits);
	free(number);
	number = (char *)calloc(len, sizeof(char));
	if (!number)
	{
		throw "Memory allocation error";
	}
	if (digits[0] == '-')
	{
		sign = '-';
		for (int i = 0; i < len - 1; i++)
		{
			number[i] = digits[len - i - 1];
		}
		len--;
	}
	else
	{
		for (int i = 0; i < len; i++)
		{
			number[i] = digits[len - i - 1];
		}
	}
}

LN::LN(const string string_number)
{
	if (string_number == "NaN")
	{
		NaN = true;
		free(number);
		number = (char *)calloc(1, sizeof(char));
		if (!number)
		{
			throw "Memory allocation error";
		}
		number[0] = '0';
	}
	else
	{
		len = string_number.size();
		free(number);
		number = (char *)calloc(len, sizeof(char));
		if (!number)
		{
			throw "Memory allocation error";
		}
		if (string_number[0] == '-')
		{
			sign = '-';
			for (int i = 0; i < len - 1; i++)
			{
				number[i] = string_number[len - i - 1];
			}
			len--;
		}
		else
		{
			sign = '+';
			for (int i = 0; i < len; i++)
			{
				number[i] = string_number[len - i - 1];
			}
		}
	}
}

LN::LN(const string_view string_number)
{
	if (string_number == "NaN")
	{
		NaN = true;
		free(number);
		number = (char *)calloc(1, sizeof(char));
		if (!number)
		{
			throw "Memory allocation error";
		}
		number[0] = '0';
	}
	else
	{
		len = string_number.size();
		free(number);
		number = (char *)calloc(len, sizeof(char));
		if (!number)
		{
			throw "Memory allocation error";
		}
		if (string_number[0] == '-')
		{
			sign = '-';
			for (int i = 0; i < len - 1; i++)
			{
				number[i] = string_number[len - i - 1];
			}
			len--;
		}
		else
		{
			sign = '+';
			for (int i = 0; i < len; i++)
			{
				number[i] = string_number[len - i - 1];
			}
		}
	}
}

LN::LN(const LN &other)
{
	NaN = other.NaN;
	sign = other.sign;
	len = other.len;
	free(number);
	number = (char *)calloc(len, sizeof(char));

	if (number == nullptr)
	{
		throw "Memory allocation error";
	}

	for (int i = 0; i < other.len; i++)
	{
		number[i] = other.number[i];
	}
}

LN::LN(LN &&other) noexcept
{
	NaN = other.NaN;
	sign = other.sign;
	len = other.len;
	free(number);
	number = other.number;
	other.number = nullptr;
	other.len = 0;
}

LN::~LN()
{
	free(number);
}

LN &LN::operator=(const LN &other)
{
	if (this != &other)
	{
		NaN = other.NaN;
		sign = other.sign;
		len = other.len;
		free(number);
		number = (char *)calloc(len, sizeof(char));
		if (!number)
		{
			throw "Memory allocation error";
		}
		for (int i = 0; i < len; i++)
		{
			number[i] = other.number[i];
		}
	}
	return *this;
}

LN &LN::operator=(LN &&other) noexcept
{
	if (*this != other)
	{
		NaN = other.NaN;
		sign = other.sign;
		len = other.len;
		free(number);
		number = other.number;
		other.number = nullptr;
		other.len = 0;
	}
	return *this;
}

LN LN::operator+(const LN &other) const
{
	if (NaN || other.NaN)
	{
		return LN("NaN");
	}

	if (sign == '+' && other.sign == '-')
	{
		return *this - (-other);
	}
	if (sign == '-' && other.sign == '+')
	{
		return other - (-*this);
	}
	if (sign == '-' && other.sign == '-')
	{
		return -((-*this) + (-other));
	}
	if (*this < other)
	{
		return other + *this;
	}
	char *c = (char *)calloc(len + 1, sizeof(char));
	if (!c)
	{
		throw "Memory error";
	}
	int shift = 0;
	for (int i = 0; i < other.len; i++)
	{
		c[i] = ((number[i] - '0' + other.number[i] - '0' + shift) % 10) + '0';
		shift = (number[i] - '0' + other.number[i] - '0' + shift) / 10;
	}
	for (int i = other.len; i < len; i++)
	{
		c[i] = ((number[i] - '0' + shift) % 10) + '0';
		shift = (number[i] - '0' + shift) / 10;
	}
	LN ret;
	if (shift > 0)
	{
		c[len] = '1';
		ret.NaN = false;
		ret.len = len + 1;
		ret.sign = '+';
		ret.number = c;
		return ret;
	}
	else
	{
		ret.NaN = false;
		ret.len = len;
		ret.sign = '+';
		ret.number = c;
		return ret;
	}
}

LN LN::operator-() const
{
	if (NaN)
	{
		return LN("NaN");
	}
	if (*this == LN())
	{
		return LN();
	}
	LN ret;
	if (sign == '+')
	{
		ret.sign = '-';
	}
	else
	{
		ret.sign = '+';
	}
	ret.len = len;
	free(ret.number);
	ret.number = (char *)calloc(len, sizeof(char));

	if (!ret.number)
	{
		throw "Memory error";
	}

	for (int i = 0; i < ret.len; i++)
	{
		ret.number[i] = number[i];
	}

	return ret;
}

LN LN::operator-(const LN &other) const
{
	if (NaN || other.NaN)
	{
		return LN("NaN");
	}
	if (sign == '+' && other.sign == '-')
	{
		return *this + (-other);
	}
	if (sign == '-' && other.sign == '+')
	{
		return -((-*this) + other);
	}
	if (sign == '-' && other.sign == '-')
	{
		return (-other) - (-*this);
	}
	if (*this < other)
	{
		return -(other - *this);
	}
	char *c = (char *)calloc(len, sizeof(char));
	if (!c)
	{
		throw "Memory error";
	}
	int shift = 0;
	int start = 1;
	for (int i = 0; i < other.len; i++)
	{
		if (number[i] - other.number[i] + shift < 0)
		{
			c[i] = ((10 + number[i] - other.number[i] + shift) % 10) + '0';
			shift = -1;
		}
		else
		{
			c[i] = ((number[i] - other.number[i] + shift) % 10) + '0';
			shift = 0;
		}
		if (c[i] > '0')
		{
			start = i + 1;
		}
	}
	for (int i = other.len; i < len; i++)
	{
		if (number[i] - '0' + shift < 0)
		{
			c[i] = ((10 + number[i] - '0' + shift) % 10) + '0';
			shift = -1;
		}
		else
		{
			c[i] = ((number[i] - '0' + shift) % 10) + '0';
			shift = 0;
		}
		if (c[i] > '0')
		{
			start = i + 1;
		}
	}
	char *b = (char *)realloc(c, start);
	if (!b)
	{
		free(c);
		throw "Memory error";
	}
	LN res;
	res.NaN = false;
	res.sign = '+';
	res.len = start;
	res.number = b;
	return res;
}

LN LN::operator*(const LN &other) const
{
	if (NaN || other.NaN)
	{
		return LN("NaN");
	}
	if (*this == LN() || other == LN())
	{
		LN ret;
		ret.len = 1;
		free(ret.number);
		ret.number = (char *)calloc(1, sizeof(char));
		ret.number[0] = '0';

		return ret;
	}
	if (sign == '+' && other.sign == '-')
	{
		return -(*this * (-other));
	}
	if (sign == '-' && other.sign == '+')
	{
		return -((-*this) * other);
	}
	if (sign == '-' && other.sign == '-')
	{
		return (-*this) * (-other);
	}
	if (*this < other)
	{
		return other * (*this);
	}
	char *c = (char *)calloc(len + other.len, sizeof(char));
	if (!c)
	{
		throw "Memory error";
	}
	for (int i = 0; i < len + other.len; i++)
	{
		c[i] = '0';
	}
	int start = 1;
	for (int i = 0; i < len; i++)
	{
		int rest = 0;
		for (int j = 0; j < other.len; j++)
		{
			int val = (c[i + j] - '0') + (number[i] - '0') * (other.number[j] - '0') + rest;
			c[i + j] = (val % 10) + '0';
			rest = val / 10;
			if (c[i + j] > '0')
			{
				start = i + j + 1;
			}
		}
		if (rest > 0)
		{
			for (int j = other.len; j < other.len + len; j++)
			{
				int val = (c[i + j] - '0') + rest;
				c[i + j] = (val % 10) + '0';
				rest = val / 10;
				if (c[i + j] > '0')
				{
					start = i + j + 1;
				}
				if (rest == 0)
				{
					break;
				}
			}
		}
	}
	LN res;
	res.sign = '+';
	res.len = start;
	res.NaN = false;
	res.number = c;
	return res;
}

LN LN::operator/(const LN &other) const
{
	if (other == LN() || NaN || other.NaN)
	{
		return LN("NaN");
	}
	if (sign == '+' && other.sign == '-')
	{
		return -(*this / (-other));
	}
	if (sign == '-' && other.sign == '+')
	{
		return -((-*this) / other);
	}
	if (sign == '-' && other.sign == '-')
	{
		return (-*this) / (-other);
	}
	if (*this < other)
	{
		return LN();
	}
	if (other == LN(1))
	{
		return *this;
	}
	if (other == LN(2))
	{
		char *c = (char *)calloc(len, sizeof(char));
		int shift = 0;
		for (int i = 0; i < len; i++)
		{
			c[len - i - 1] = ((number[len - i - 1] - '0' + 10 * shift) / 2) + '0';
			shift = (number[len - i - 1] - '0' + 10 * shift) % 2;
		}
		int cnt = len;
		if (c[len - 1] == '0')
			cnt--;
		LN res;
		res.NaN = false;
		res.sign = '+';
		res.len = cnt;
		res.number = c;
		return res;
	}
	LN l = LN();
	LN r = *this + LN(1);
	while (r > l + LN(1))
	{
		LN m = (r + l) / LN(2);
		if (m * other <= *this)
		{
			l = m;
		}
		else
		{
			r = m;
		}
	}
	return l;
}

LN LN::operator%(const LN &other) const
{
	if (NaN || other.NaN)
	{
		return LN("NaN");
	}
	//	cout << *this << " % " << other << "\n";
	LN div = (*this) / other;
	//	cout << *this << " / " << other << " = " << div << "\n";
	return *this - (other * div);
}

LN LN::sqrt() const
{
	//	cout << *this << "\n";
	if (*this < LN() || NaN)
	{
		return LN("NaN");
	}
	LN l = LN();
	LN r = *this + LN(1);
	while (r > l + LN(1))
	{
		LN m = (l + r) / LN(2);
		if (m * m <= *this)
		{
			l = m;
		}
		else
		{
			r = m;
		}
	}
	return l;
}

void LN::operator+=(const LN &other)
{
	*this = *this + other;
}

void LN::operator-=(const LN &other)
{
	*this = *this - other;
}

void LN::operator*=(const LN &other)
{
	*this = *this * other;
}

void LN::operator/=(const LN &other)
{
	*this = *this / other;
}

void LN::operator%=(const LN &other)
{
	*this = *this % other;
}

bool LN::operator>(const LN &other) const noexcept
{
	if (NaN || other.NaN)
	{
		return false;
	}
	if (sign == '-' && other.sign == '+')
	{
		return false;
	}
	if (sign == '+' && other.sign == '-')
	{
		return true;
	}
	if (sign == '-' && other.sign == '-')
	{
		return ((-*this) < (-other));
	}
	if (len < other.len)
	{
		return false;
	}
	if (len > other.len)
	{
		return true;
	}
	//	cout << *this << " > " << other << "?\n";
	for (int i = 0; i < len; i++)
	{
		if (number[len - i - 1] > other.number[len - i - 1])
		{
			//			cout << "1\n";
			return true;
		}
		if (number[len - i - 1] < other.number[len - i - 1])
		{
			//			cout << "0\n";
			return false;
		}
	}
	return false;
}

bool LN::operator==(const LN &other) const noexcept
{
	if (NaN || other.NaN)
	{
		return false;
	}
	if (sign != other.sign)
	{
		return false;
	}
	if (len != other.len)
	{
		return false;
	}
	for (int i = 0; i < len; i++)
	{
		if (number[i] != other.number[i])
		{
			return false;
		}
	}
	return true;
}

bool LN::operator<(const LN &other) const noexcept
{
	if (NaN || other.NaN)
	{
		return false;
	}
	return !(*this > other || *this == other);
}

bool LN::operator<=(const LN &other) const noexcept
{
	if (NaN || other.NaN)
	{
		return false;
	}
	return !(*this > other);
}

bool LN::operator>=(const LN &other) const noexcept
{
	if (NaN || other.NaN)
	{
		return false;
	}
	return !(*this < other);
}

bool LN::operator!=(const LN &other) const noexcept
{
	if (NaN || other.NaN)
	{
		return true;
	}

	return !(*this == other);
}

bool LN::isNaN() const
{
	return NaN;
}

int LN::length() const
{
	return len;
}

char LN::getSign() const
{
	return sign;
}

char *LN::getNumber() const
{
	return number;
}

ostream &operator<<(ostream &out, const LN &object)
{
	if (object.NaN)
	{
		out << "NaN";
	}
	else
	{
		if (object.sign == '-')
		{
			out << "-";
		}
		for (int i = object.len - 1; i >= 0; i--)
		{
			out << object.number[i];
		}
	}

	return out;
}

LN::operator long long() const
{
	if (len > 19)
	{
		throw "Number is too big";
	}
	else
	{
		if (len == 10)
		{
			char min_max_long[19] = {
				'7', '0', '8', '5', '7', '7', '4', '5', '8', '6', '3', '0', '2', '7', '3', '3', '2', '2', '9'
			};
			if (sign == '-')
			{
				min_max_long[0] = '8';
			}

			for (int i = 18; i >= 0; i--)
			{
				if (min_max_long[i] > number[i])
				{
					break;
				}
				else if (min_max_long[i] < number[i])
				{
					throw "Number is too big";
				}
			}
		}
		long long val = 0;
		for (int i = 0; i < len; i++)
		{
			val *= 10;
			if (sign)
			{
				val -= number[i];
			}
			else
			{
				val += number[i];
			}
		}
		return val;
	}
}

LN::operator bool() const
{
	if (*this == LN())
	{
		return false;
	}
	else
	{
		return true;
	}
}

LN operator"" _ln(const char *str)
{
	return LN(str);
}