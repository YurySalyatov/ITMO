#include "phonebook.h"
#include "quicksort.h"
#include "return_codes.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

typedef struct phonebook phonebook;
std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
void log(const std::string msg)
{
	std::cerr << msg << "\n";
}

int get_random()
{
	return (mt() ^ (mt() << 16)) % INT32_MAX;
}

template< typename T >
void quick_sort1(std::vector< T > &array, const int start, const int end)
{
	if (end - start <= 1)
	{
		return;
	}
	T x = array[start + get_random() % (end - start)];
	int l0 = 0, l1 = 0, l2 = 0;
	for (int i = start; i < end; i++)
	{
		if (x < array[i])
		{
			l2++;
			continue;
		}
		if (array[i] < x and l1 >= 1)
		{
			std::swap(array[i], array[start + l0]);
			l0++;
			l1--;
		}
		std::swap(array[i], array[start + l0 + l1]);
		if (array[start + l0 + l1] < x)
		{
			l0++;
		}
		else
		{
			l1++;
		}
	}
	quick_sort1< T >(array, start, start + l0);
	quick_sort1< T >(array, end - l2, end);
}

template< typename T >
int partition(std::vector< T > &arr, int low, int high)
{
	T pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			std::swap(arr[i], arr[j]);
		}
	}
	std::swap(arr[i + 1], arr[high]);
	return (i + 1);
}

template< typename T >
void quickSort(std::vector< T > &arr, int low, int high)
{
	while (low < high)
	{
		int pi = partition(arr, low, high);

		if (pi - low < high - pi)
		{
			quickSort(arr, low, pi - 1);
			low = pi + 1;
		}
		else
		{
			quickSort(arr, pi + 1, high);
			high = pi - 1;
		}
	}
}

template< typename T, bool descending >
void quick_sort(std::vector< T > &s, const int size)
{
	// quick_sort1(s, 0, size);
	quickSort< T >(s, 0, size - 1);
	if (descending)
	{
		for (int i = 0; i < size / 2; i++)
		{
			std::swap(s[i], s[size - i - 1]);
		}
	}
}

template< typename T >
void solve(std::ifstream &in, std::ofstream &out, const int size, const bool reversed)
{
	std::vector< T > s(size);
	for (int i = 0; i < size; i++)
	{
		in >> s[i];
	}

	if (reversed)
	{
		quick_sort< T, true >(s, size);
	}
	else
	{
		quick_sort< T, false >(s, size);
	}

	for (T x : s)
	{
		out << x << "\n";
	}

	s.clear();
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		log("not enough arguments");
		return ERROR_INVALID_PARAMETER;
	}

	std::ifstream in(argv[1]);
	if (in.fail())
	{
		log("input file wasn't found");
		return ERROR_FILE_NOT_FOUND;
	}

	std::string type, flag;
	int n;
	in >> type >> flag >> n;

	bool reversed;
	if (flag == "ascending")
	{
		reversed = false;
	}
	else if (flag == "descending")
	{
		reversed = true;
	}
	else
	{
		in.close();
		log("Unknown sorting parameter");
		return ERROR_INVALID_DATA;
	}

	std::ofstream out(argv[2]);
	if (type == "phonebook")
	{
		solve< phonebook >(in, out, n, reversed);
	}
	else if (type == "int")
	{
		solve< int >(in, out, n, reversed);
	}
	else if (type == "float")
	{
		solve< float >(in, out, n, reversed);
	}
	else
	{
		out.close();
		in.close();
		log("invalid data type");
		return ERROR_INVALID_DATA;
	}

	out.close();
	in.close();
	return 0;
}