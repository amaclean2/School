#ifndef IMAGEMAKER_H
#define IMAGEMAKER_H

#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <iomanip>

using namespace std;

const int MAX_WIDTH = 640;
const int MAX_HEIGHT = 480;
const int MAX_COLOR = 255;

enum COLOR { RED, GREEN, BLUE };

class ImageMaker
{
public:
	ImageMaker();
	ImageMaker(const string& filename);
	void LoadImage(const string& filename);
	void SaveImage(const string& filename); // Write the matrix to file

	// Size functions
	int GetWidth() const;
	int GetHeight() const;
	void SetWidth(int newWidth);
	void SetHeight(int newHeight);
	// Color functions
	int GetRed() const;
	int GetGreen() const;
	int GetBlue() const;
	void SetRed(int newR);
	void SetGreen(int newG);
	void SetBlue(int newB);
	// Drawing methods
	void FillCanvas();
	void DrawPixel(int x, int y);
	void DrawRectangle(int x1, int y1, int x2, int y2);
	void FillRect(int x1, int y1, int x2, int y2);
	void DrawLine(int x1, int y1, int x2, int y2);
private:
	int width;
	int height;
	int red;
	int green;
	int blue;
	short image[MAX_WIDTH][MAX_HEIGHT][3];
};

#endif