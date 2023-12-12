#include "LN.h"
#include "return_codes.h"

#include <cstdio>
#include <fstream>
#include <stack>
using namespace std;

int main()
{
	try {
		LN A(2000);
		LN B(2);
		LN C = A / B;
		LN D(256);
		LN F(64);
			C -= LN(9);
		cout << C << endl;
		cout << A << endl;
		cout << (A < F) << endl;
		cout << (A < D) << endl;
	} catch (string e) {
		cout << e << endl;
		return 0;
	}
	return 0;
}