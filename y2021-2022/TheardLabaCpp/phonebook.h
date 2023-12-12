#include <fstream>
#include <iostream>
struct PhoneBook
{
	std::string first_name;
	std::string second_name;
	std::string third_name;
	long long phone_number;
	PhoneBook(const std::string &second, const std::string &first, const std::string &third, unsigned long phone);
	PhoneBook();
	bool operator==(const PhoneBook &second) const;
	bool operator>(const PhoneBook &second) const;
	bool operator<(const PhoneBook &second) const;
};
std::istream &operator>>(std::istream &in, PhoneBook &phonebook);
std::ostream &operator<<(std::ostream &out, const PhoneBook &phonebook);