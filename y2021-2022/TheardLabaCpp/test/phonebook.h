#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
struct phonebook
{
	std::string a;
	std::string b;
	std::string c;
	long long num;
};
std::istream& operator>>(std::istream& in, phonebook& a);
std::ostream& operator<<(std::ostream& out, phonebook& a);
bool operator<(const phonebook& a, const phonebook& b);
bool operator>(const phonebook& a, const phonebook& b);
bool operator==(const phonebook& a, const phonebook& b);