#include <iostream>
#include <time.h>
#include "ImageMaker.h"

using namespace std;

int main()
{
	ImageMaker *image = new ImageMaker("img.ppm");
	image->SetRed(500);
	image->SetRed(255);
	image->SetWidth(500);
	image->SetHeight(500);
	image->FillCanvas();
	
	image->SetRed(255);
	image->SetGreen(51);
	image->SetBlue(51);
	int xStart = 250;
	int yStart = 250;
	for (int x = 100; x < 400; x++)
	{
		image->DrawLine(xStart, yStart, x, 100);
	}
	for (int y = 100; y < 400; y++)
	{
		image->DrawLine(xStart, yStart, 100, y);
	}
	image->DrawLine(250, 250, 400, 400);
	image->SetGreen(255);
	image->SetRed(0);
	image->SetBlue(0);
	image->DrawPixel(250, 250);
	image->DrawRectangle(100, 100, 400, 400);
	image->SetBlue(250);
	image->SetRed(100);
	image->SetGreen(20);
	image->FillRect(300, 300, 400, 400);

	image->SaveImage("img.txt");
	image->LoadImage("img.txt");
	image->DrawLine(250, 250, 400, 250);
	image->SaveImage("img.txt");

	system("pause");
	return 0;
}