#include "imageMaker.h"


ImageMaker::ImageMaker()
{
	width = 0;
	height = 0;
	red = 0;
	green = 0;
	blue = 0;
}
ImageMaker::ImageMaker(const string& filename)
{
	//creates a new file with an empty canvas
	width = 0;
	height = 0;
	red = 0;
	green = 0;
	blue = 0;
	ofstream output;
	output.open(filename);
	output << "P3" << endl;
	output << width << " " << height << endl;
	output << 255 << endl;
}
void ImageMaker::LoadImage(const string& filename)
{
	string line;
	string token;
	queue<string> tokens;
	int charCount = 0;
	int size;
	ifstream input(filename);
	if (input.is_open())
	{
		while (getline(input, line))
		{
			size = line.size();
			token = "";
			charCount = 0;
			while (charCount < size)
			{
				if (line[charCount] != ' ')
					token.push_back(line[charCount]);
				if (line[charCount] == ' ' || charCount == size - 1)
				{
					tokens.push(token);
					token = "";
				}
				charCount++;
			}
		}
		
		tokens.pop();
		width = stoi(tokens.front());
		tokens.pop();
		height = stoi(tokens.front());
	}
}
void ImageMaker::SaveImage(const string& filename)// Write the matrix to file
{
	ofstream output;
	output.open(filename);
	output << "P3" << endl;
	output << width << " " << height << endl;
	output << 255 << endl;

	//adds color to drawn pixels
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			output << setw(3) << image[i][j][0] << " ";
			output << setw(3) << image[i][j][1] << " ";
			output << setw(3) << image[i][j][2] << " ";
		}
		output << endl;
	}
}
									 // Size functions
int ImageMaker::GetWidth() const
{
	return width;
}
int ImageMaker::GetHeight() const
{
	return height;
}
void ImageMaker::SetWidth(int newWidth)
{
	if (newWidth < 0)
		cerr << "Width must be positive" << endl;
	else
		width = newWidth;
}
void ImageMaker::SetHeight(int newHeight)
{
	if (newHeight < 0)
		cerr << "Height must be positive" << endl;
	else
		height = newHeight;
}
	// Color functions
int ImageMaker::GetRed() const
{
	return red;
}
int ImageMaker::GetGreen() const
{
	return green;
}
int ImageMaker::GetBlue() const
{
	return blue;
}
void ImageMaker::SetRed(int newR)
{
	if (newR > 255)
		cerr << "Not a color in the range" << endl;
	else
		red = newR;
}
void ImageMaker::SetGreen(int newG)
{
	if (newG > 255)
		cerr << "Not a color in the range" << endl;
	else
		green = newG;
}
void ImageMaker::SetBlue(int newB)
{
	if (newB > 255)
		cerr << "Not a color in the range" << endl;
	else
		blue = newB;
}
// Drawing methods
void ImageMaker::FillCanvas()
{
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			image[i][j][0] = 0;
			image[i][j][1] = 0;
			image[i][j][2] = 0;
		}
	}
}
void ImageMaker::DrawPixel(int x, int y)
{
	if (x >= width || y >= height || x < 0 || y < 0)
		cerr << "Pixel out of range" << endl;
	else
	{
		image[x][y][0] = red;
		image[x][y][1] = green;
		image[x][y][2] = blue;
	}
}
void ImageMaker::DrawRectangle(int x1, int y1, int x2, int y2)
{
	if (x1 >= width || y1 >= height || x1 < 0 || y1 < 0)
		cerr << "Pixel out of range" << endl;
	else if (x2 >= width || y2 >= height || x2 < 0 || y2 < 0)
		cerr << "Pixel out of range" << endl;
	else if (x1 > x2 || y1 > y2)
		cerr << "Rectanges must be drawn from upper left corner to lower right corner" << endl;
	else
	{
		int changeInX = x1;
		while (changeInX < x2)
		{
			DrawPixel(changeInX, y1);
			DrawPixel(changeInX, y2);
			changeInX++;
		}
		int changeInY = y1;
		while (changeInY < y2)
		{
			DrawPixel(x1, changeInY);
			DrawPixel(x2, changeInY);
			changeInY++;
		}
	}
	
}
void ImageMaker::FillRect(int x1, int y1, int x2, int y2)
{
	if (x1 >= width || y1 >= height || x1 < 0 || y1 < 0)
		cerr << "Pixel out of range" << endl;
	else if (x2 >= width || y2 >= height || x2 < 0 || y2 < 0)
		cerr << "Pixel out of range" << endl;
	else if (x1 > x2 || y1 > y2)
		cerr << "Rectanges must be drawn from upper left corner to lower right corner" << endl;
	else
	{
		int x = x1;
		for (int x = x1; x < x2; x++)
		{
			for (int y = y1; y < y2; y++)
				DrawPixel(x, y);
		}
	}
}
void ImageMaker::DrawLine(int x1, int y1, int x2, int y2)
{
	if (x1 >= width || y1 >= height || x1 < 0 || y1 < 0)
		cerr << "Pixel out of range" << endl;
	else if (x2 >= width || y2 >= height || x2 < 0 || y2 < 0)
		cerr << "Pixel out of range" << endl;
	else
	{
		int xLen = x2 - x1;
		int yLen = y2 - y1;
		int xPos = x1;
		int yPos = y1;
		int xSegment = 0;
		int ySegment = 0;
		if (xLen != 0 && yLen != 0)
		{
			xSegment = xLen / yLen;
			ySegment = yLen / xLen;
		}
		else if (xLen == 0)
		{
			if (y1 < y2)
			{
				while (yPos < y2)
				{
					DrawPixel(xPos, yPos);
					yPos++;
				}
			}
			else
			{
				while (yPos > y2)
				{
					DrawPixel(xPos, yPos);
					yPos--;
				}
			}
			return;
		}
		else if (yLen == 0)
		{
			if (x1 < x2)
			{
				while (xPos < x2)
				{
					DrawPixel(xPos, yPos);
					xPos++;
				}
			}
			else
			{
				while (xPos < y2)
				{
					DrawPixel(xPos, yPos);
					xPos++;
				}
			}

			return;
		}
		int xSegPos = 0;
		int ySegPos = 0;
		//works for lines shallower than 45 degrees

		//x going to the right y going down
		if (xLen > 0 && yLen > 0)
		{
			if (abs(xSegment) >= abs(ySegment))
			{
				while (xPos < x2)
				{
					DrawPixel(xPos, yPos);
					if (xSegPos < abs(xSegment))
					{
						xPos++;
						xSegPos++;
					}
					else
					{
						xSegPos = 0;
						yPos++;
					}
				}
			}
			//works for lines steeper than 45 degrees
			else
			{
				while (yPos < y2)
				{
					DrawPixel(xPos, yPos);
					if (ySegPos < abs(ySegment))
					{
						yPos++;
						ySegPos++;
					}
					else
					{
						ySegPos = 0;
						xPos++;
					}
				}
			}
		}
		//x going to the left y going down
		else if (xLen < 0 && yLen > 0)
		{
			if (abs(xSegment) >= abs(ySegment))
			{
				while (xPos > x2)
				{
					DrawPixel(xPos, yPos);
					if (abs(xSegPos) < abs(xSegment))
					{
						xPos--;
						xSegPos++;
					}
					else
					{
						xSegPos = 0;
						yPos++;
					}
				}
			}
			//works for lines steeper than 45 degrees
			else
			{
				while (yPos < y2)
				{
					DrawPixel(xPos, yPos);
					if (ySegPos < abs(ySegment))
					{
						yPos++;
						ySegPos++;
					}
					else
					{
						ySegPos = 0;
						xPos--;
					}
				}
			}
		}
		//y going up x going to the right
		else if (xLen > 0 && yLen < 0)
		{
			if (abs(xSegment) >= abs(ySegment))
			{
				while (xPos < x2)
				{
					image[xPos][yPos][0] = red;
					image[xPos][yPos][1] = green;
					image[xPos][yPos][2] = blue;
					if (xSegPos < abs(xSegment))
					{
						xPos++;
						xSegPos++;
					}
					else
					{
						xSegPos = 0;
						yPos++;
					}
				}
			}
			//works for lines steeper than 45 degrees
			else
			{
				while (yPos > y2)
				{
					DrawPixel(xPos, yPos);
					if (abs(ySegPos) < abs(ySegment))
					{
						yPos--;
						ySegPos++;
					}
					else
					{
						ySegPos = 0;
						xPos++;
					}
				}
			}
		}
		//x to the left y up
		else if (xLen < 0 && yLen < 0)
		{
			if (abs(xSegment) >= abs(ySegment))
			{
				while (xPos > x2)
				{
					DrawPixel(xPos, yPos);
					if (abs(xSegPos) < abs(xSegment))
					{
						xPos--;
						xSegPos--;
					}
					else
					{
						xSegPos = 0;
						yPos--;
					}
				}
			}
			//works for lines steeper than 45 degrees
			else
			{
				while (yPos > y2)
				{
					DrawPixel(xPos, yPos);
					if (abs(ySegPos) < abs(ySegment))
					{
						yPos--;
						ySegPos++;
					}
					else
					{
						ySegPos = 0;
						xPos--;
					}
				}
			}
		}
	}
	

}
