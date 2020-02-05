// Needed includes
#include "Draw.h"

// Colors
enum color { red = RGB(255, 0, 0), yellow = RGB(255, 255, 0), green = RGB(0, 255, 0), gray = RGB(211, 211, 211), black = RGB(0,0,0) };

// Part 1: Draw traffic light
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
void roads(HDC hdc, RECT rect)
{

	// Init
	int left = 0;
	int top = 0;
	int right = 0;
	int bottom = 0;
	
	// Middle

	HBRUSH hb = CreateSolidBrush(gray);
	HGDIOBJ h = SelectObject(hdc, hb);

	// Draw West - East Road
	left = rect.right; // Length
	top = 350; // Top starting
	right = 0; // Starting point
	bottom = 550; // Bottom starting

	Rectangle(hdc, left, top, right, bottom);

	left = 850; // Left starting
	top = 0; // Top starting
	right = 1050; // Right ending
	bottom = rect.bottom; // Length

	Rectangle(hdc, left, top, right, bottom);

	// Lines
	MoveToEx(hdc, 850, 350, NULL);
	LineTo(hdc, 1050, 350);

	MoveToEx(hdc, 850, 550, NULL);
	LineTo(hdc, 1050, 550);


	HPEN hPen = CreatePen(PS_DASH, 2, yellow);
	HGDIOBJ holdPen = SelectObject(hdc, hPen);
	
	MoveToEx(hdc, 0, 450, NULL);
	LineTo(hdc, 850, 450);

	MoveToEx(hdc, 1050, 450, NULL);
	LineTo(hdc, rect.right, 450);

	MoveToEx(hdc, 950, 0, NULL);
	LineTo(hdc, 950, 350);

	MoveToEx(hdc, 950, 550, NULL);
	LineTo(hdc, 950, rect.bottom);

	SelectObject(hdc, holdPen);
	DeleteObject(hPen);
	SelectObject(hdc, h);
	DeleteObject(hb);
}

