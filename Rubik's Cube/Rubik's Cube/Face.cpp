#include <iostream>
#include "Row.cpp"

using namespace std;

class Face
{
public:
	Face()
	{
		for (int i = 0; i < 3; i++)
			Row row = new Row;
	}
private:
	int face[3];
};