#include "phonebook.h"
#include "quicksort.h"
#include "return_codes.h"
#include <cstdio>
#include <ctime>
#include <string>
#include <vector>
using namespace std;
typedef struct PhoneBook PhoneBook;
template< typename T, bool descending >
void quicksort(std::vector< T > &array, size_t start, size_t end)
{
	srand(time(nullptr));
	if (end - start <= 1)
	{
		return;
	}
	while (start < end)
	{
		T x = array[start + rand() % (end - start)];
		size_t l0 = 0, l1 = 0, l2 = 0;
		for (size_t i = start; i < end; i++)
		{
			if ((array[i] > x && !descending) || (array[i] < x && descending))
			{
				l2++;
				continue;
			}
			if (((array[i] < x && !descending) || (array[i] > x && descending)) && l1 >= 1)
			{
				std::swap(array[i], array[start + l0]);
				l0++;
				l1--;
			}
			std::swap(array[i], array[start + l0 + l1]);
			if ((array[start + l0 + l1] < x && !descending) || (array[start + l0 + l1] > x && descending))
			{
				l0++;
			}
			else
			{
				l1++;
			}
		}
		if (l0 < l2)
		{
			quicksort< T, descending >(array, start, start + l0);
			start = start + l0 + l1;
		}
		else
		{
			quicksort< T, descending >(array, end - l2, end);
			end = end - l2 - l1;
		}
	}
}
template< typename T >
void sort(size_t n, ifstream &filein, const string &out, int &error, const bool &reverse)
{
	vector< T > sorted(n);
	T x;
	try
	{
		sorted.assign(n, x);
	} catch (length_error &er)
	{
		filein.close();
		cerr << "Not enough memory for vector" << endl;
		error = 1;
		return;
	}
	for (size_t i = 0; i < n; i++)
	{
		filein >> sorted[i];
	}
	if (reverse)
	{
		quicksort< T, true >(sorted, 0, n);
	}
	else
	{
		quicksort< T, false >(sorted, 0, n);
	}
	ofstream fileout;
	fileout.open(out);
	if (!fileout)
	{
		filein.close();
		sorted.clear();
		cerr << "Can't open file with path: " << out << ", please check it" << endl;
		error = 1;
		return;
	}
	for (const T &k : sorted)
	{
		fileout << k << "\n";
	}
	sorted.clear();
	fileout.close();
	filein.close();
}
int main(int argv, char *args[])
{
	if (argv != 3)
	{
		cerr << "Expected three arguments in cmd, but was given " << argv << endl;
		return ERROR_INVALID_PARAMETER;
	}
	ifstream filein;
	filein.open(args[1]);
	if (!filein)
	{
		cerr << "Can't open file with path: " << args[1] << ", please check it" << endl;
		return ERROR_NOT_FOUND;
	}
	string type_of_items, reverse;
	size_t count_items;
	filein >> type_of_items;
	filein >> reverse;
	filein >> count_items;
	int error = 0;
	bool revers;
	if (reverse == "descending")
	{
		revers = true;
	}
	else
	{
		revers = false;
	}
	if (type_of_items == "phonebook")
	{
		sort< PhoneBook >(count_items, filein, args[2], error, revers);
	}
	else
	{
		if (type_of_items == "int")
		{
			sort< int >(count_items, filein, args[2], error, revers);
		}
		else
		{
			if (type_of_items == "float")
			{
				sort< float >(count_items, filein, args[2], error, revers);
			}
			else
			{
				cerr << "Unsupported type of compare items in file";
				return ERROR_INVALID_DATA;
			}
		}
	}
	if (error)
	{
		return ERROR_INVALID_PARAMETER;
	}
	return 0;
}