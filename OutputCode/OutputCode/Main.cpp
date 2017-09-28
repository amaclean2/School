#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	string line;
	ifstream input("Main.cpp");
	if (input.is_open())
	{
		while (getline(input, line))
		{
			cout << line << endl;
		}
		input.close();
	}

	system("pause");
	return 0;
}