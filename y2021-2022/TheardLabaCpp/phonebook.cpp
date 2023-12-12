#include "phonebook.h"
PhoneBook::PhoneBook(const std::string &second, const std::string &first, const std::string &third, unsigned long phone)
{
	second_name = second;
	first_name = first;
	third_name = third;
	phone_number = phone;
}
PhoneBook::PhoneBook()
{
	second_name = " max number of char ";
	first_name = " max number of char ";
	third_name = " max number of char ";
	phone_number = 0;
}
bool PhoneBook::operator==(const PhoneBook &second) const
{
	if (first_name == second.first_name && second_name == second.second_name && third_name == second.third_name &&
		phone_number == second.phone_number)
		return true;
	return false;
}
bool PhoneBook::operator>(const PhoneBook &second) const
{
	if (second_name > second.second_name || (second_name == second.second_name && first_name > second.first_name) ||
		(second_name == second.second_name && first_name == second.first_name && third_name > second.third_name) ||
		(second_name == second.second_name && first_name == second.first_name && third_name == second.third_name &&
		 phone_number > second.phone_number))
		return true;
	return false;
}
bool PhoneBook::operator<(const PhoneBook &second) const
{
	if (second_name < second.second_name || (second_name == second.second_name && first_name < second.first_name) ||
		(second_name == second.second_name && first_name == second.first_name && third_name < second.third_name) ||
		(second_name == second.second_name && first_name == second.first_name && third_name == second.third_name &&
		 phone_number < second.phone_number))
		return true;
	return false;
}
std::istream &operator>>(std::istream &in, PhoneBook &phonebook)
{
	in >> phonebook.second_name >> phonebook.first_name >> phonebook.third_name >> phonebook.phone_number;
	return in;
}
std::ostream &operator<<(std::ostream &out, const PhoneBook &phonebook)
{
	return out
		<< phonebook.second_name << " " << phonebook.first_name << " " << phonebook.third_name << " " << phonebook.phone_number;
}