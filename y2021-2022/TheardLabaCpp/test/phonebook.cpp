#include "phonebook.h"
#include <fstream>
#include <iostream>
#include <string>

std::istream& operator>>(std::istream& in, phonebook& bk)
{
	in >> bk.a >> bk.b >> bk.c >> bk.num;
	return in;
}

std::ostream& operator<<(std::ostream& out, phonebook& bk)
{
	out << bk.a << " " << bk.b << " " << bk.c << " " << bk.num;
	return out;
}

bool operator<(const phonebook& bk, phonebook& ph)
{
	if (bk.a < ph.a || (bk.a == ph.a && bk.b < ph.b) || (bk.a == ph.a && bk.b == ph.b && bk.c < ph.c) ||
		(bk.a == ph.a && bk.b == ph.b && bk.c == ph.c && bk.num < ph.num))
	{
		return true;
	}
	return false;
}