// Needed includes
#include "Draw.h"

enum color { red = RGB(255, 0, 0), yellow = RGB(255, 255, 0), green = RGB(0, 255, 0), gray = RGB(211, 211, 211), black = RGB(0,0,0) };

// Functions (add in header!!!)

// Draw traffic light
void trafficlight(HDC hdc, int x, int y, bool state[])
{
	// size
	int height = 110;
	int width = 40;
	int distance = 5;

	// Brush + OBJ
	HBRUSH hb = CreateSolidBrush(black);
	HGDIOBJ h = SelectObject(hdc, hb);

	// Pole - left, top, right, bottom
	int left = x;
	int top = y;
	int right = x + width;
	int bottom = y + height;

	// Left - Right (Pole-Light)
	int leftLight = left + distance;
	int rightLight = right - distance;

	// Red (Pole)
	int topRed = top + distance;
	int bottomRed = topRed + 30;

	// Yellow (Pole)
	int topYellow = bottomRed + distance;
	int bottomYellow = topYellow + 30;

	// Green (Pole)
	int topGreen = bottomYellow + distance;
	int bottomGreen = topGreen + 30;
	

	// Draw traffic pole
	Rectangle(hdc, left, top, right, bottom);

	// Draw lights depending on state

	// Red (Light)
	if(state[0])
		hb = CreateSolidBrush(red);
	else
		hb = CreateSolidBrush(gray);
	h = SelectObject(hdc, hb);
	Ellipse(hdc, leftLight, topRed, rightLight, bottomRed);

	// Yellow (Light)
	if(state[1])
		hb = CreateSolidBrush(yellow);
	else
		hb = CreateSolidBrush(gray);
	h = SelectObject(hdc, hb);
	Ellipse(hdc, leftLight, topYellow, rightLight, bottomYellow);

	// Green (Light)
	if (state[2])
		hb = CreateSolidBrush(green);
	else
		hb = CreateSolidBrush(gray);
	h = SelectObject(hdc, hb);
	Ellipse(hdc, leftLight, topGreen, rightLight, bottomGreen);

	// Reset to original brush
	SelectObject(hdc, h);
	DeleteObject(hb);
}

// Draw roads
void road(HDC hdc, int x, int y, int length, bool dir) // dir = 0, north-south, 1 = west-east
{
	// Size
	int width = 40;

	// Road - left, top, right, bottom

	int left = 0;
	int top = 0;
	int right = 0;
	int bottom = 0;

	if (dir)
	{
		left = x;
		top = y;
		right = x + length;
		bottom = y + width;
	}
	else
	{
		left = x;
		top = y;
		right = x + width;
		bottom = y + length;
	}



	HBRUSH hb = CreateSolidBrush(gray);
	HGDIOBJ h = SelectObject(hdc, hb);

	Rectangle(hdc, left, top, right, bottom);

	SelectObject(hdc, h);
	DeleteObject(hb);
}






// Draw car


// Start
// Red
// Red + Yellow
// Green
// Yellow 
// ... Back to top


// Two roads (add later!)




