#include "LN.h"
#include "return_codes.h"

#include <fstream>
#include <stack>

using namespace std;

LN make_bin_operation(LN &first, LN &second, const string &oper)
{
	if (oper == "+")
	{
		return first + second;
	}
	if (oper == "-")
	{
		return first - second;
	}
	if (oper == "*")
	{
		return first * second;
	}
	if (oper == "/")
	{
		return first / second;
	}
	if (oper == "%")
	{
		return first % second;
	}
	if (oper == ">")
	{
		return LN(first > second);
	}
	if (oper == "==")
	{
		return LN(first == second);
	}
	if (oper == "<")
	{
		return LN(first < second);
	}
	if (oper == "<=")
	{
		return LN(first <= second);
	}
	if (oper == ">=")
	{
		return LN(first >= second);
	}
	if (oper == "!=")
	{
		return LN(first != second);
	}
}
LN make_unar_operation(LN &first, const string &oper)
{
	if (oper == "_")
	{
		return -first;
	}
	if (oper == "~")
	{
		return first.sqrt();
	}
}
int main(int argv, char **args)
{
	if (argv != 3)
	{
		cerr << "Incorrect number of arguments";
		return ERROR_INVALID_PARAMETER;
	}
	ifstream filein;
	filein.open(args[1]);
	if (!filein)
	{
		cerr << "Couldn't open input file with path " << args[1] << endl;
		return ERROR_INVALID_PARAMETER;
	}
	string a;
	stack< LN > stack;
	try
	{
		while (filein >> a)
		{
			if (a != "+" && a != "-" && a != "*" && a != "/" && a != "_" && a != "%" && a != "~" && a != "<" &&
				a != ">" && a != "<=" && a != "==" && a != ">=" && a != "!=")
			{
				stack.push(LN(a));
			}
			else if (a == "_" || a == "~")
			{
				if (stack.empty())
				{
					cerr << "Stack is empty\n";
					return ERROR_INVALID_PARAMETER;
				}
				LN first = stack.top();
				stack.pop();
				stack.push(make_unar_operation(first, a));
			}
			else
			{
				LN second, first;
				if (stack.empty())
				{
					cerr << "Stack is empty\n";
					return ERROR_INVALID_PARAMETER;
				}
				second = stack.top();
				stack.pop();
				if (stack.empty())
				{
					cerr << "Stack is empty\n";
					return ERROR_INVALID_PARAMETER;
				}
				first = stack.top();
				stack.pop();
				stack.push(make_bin_operation(first, second, a));
			}
		}
	} catch (string e)
	{
		cerr << e;
		filein.close();
		return ERROR_MEMORY;
	}
	filein.close();
	ofstream fileout;
	fileout.open(args[2]);
	if (!fileout)
	{
		cerr << "Couldn't open outfile with name " << args[2];
		return ERROR_INVALID_PARAMETER;
	}
	while (!stack.empty())
	{
		LN x = stack.top();
		stack.pop();
		fileout << x << endl;
	}
	fileout.close();
	return 0;
}
