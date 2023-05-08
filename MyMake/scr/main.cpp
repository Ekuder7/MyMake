#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>

#include "Console.hpp"

using namespace std;

void HandleError(const string& msg)
{
	cout << endl << RED_BOLD("Error: ") << msg << endl;
	cout << "Press any key to continue..." << endl;
	_getch();
	exit(-1);
}

vector<string> files;
string out;

int main(int argc, char** argv)
{
	//cout << argv[0] << endl;

	ifstream fin;
	fin.open("MyMake.mmk");

	if (!fin)
	{
		HandleError("MyMake.mmk not found");
	}

	cout << "LOG: Reading .mmk" << endl;

	string buff;
	while (!fin.eof())
	{
		getline(fin, buff);

		if (buff[0] != ':')
		{
			if (buff != "")
			{
				files.push_back(buff);
			}
		}
		else
		{
			out = buff;
			out = out.substr(1, out.size() - 1);
		}
	}
	fin.close();

	cout << "LOG: Finish reading" << endl;
	cout << "LOG: Starting compile..." << endl;

	string compile_str;
	compile_str += "g++ -std=c++98 -o2 -s -DNDEBUG "s;
	for (const string& i : files)
	{
		compile_str += (i + " ");
	}
	compile_str += " -o "s;
	compile_str += out;

	char full[300];
	_fullpath(full, "MyMake.mmk", 300);

	string path = full;

	path.erase(path.size() - 10);

	path = "cd "s + path;

	if (system(path.c_str()) != 0)
	{
		HandleError("Path is invalid");
	}

	if (system(compile_str.c_str()) == 0)
	{
		cout << "LOG: " << GREEN_BOLD("Successfully compiled!") << endl;
		cout << "LOG: File: " + out + ".exe" << endl;
	}
	else
	{
		HandleError("Compilation error");
	}

	cout << "Press any key to continue..." << endl;
	_getch();
	return 0;
}

//MyMake.mmk Example

/*

example.cpp

:example

*/
