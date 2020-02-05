#include "framework.h"
#include "Car.h"

int totalCars = 0;

Car::Car(bool dir, bool reverse, int x_val, int y_val)
{
	id = totalCars++;
	direction = dir;
	rev = reverse;
	x = x_val;
	y = y_val;
}

void Car::Draw(HDC hdc)
{

	HBRUSH hb = CreateSolidBrush(RGB(255, 0, 0));
	HGDIOBJ hOrg = SelectObject(hdc, hb);

	if(direction)
		Rectangle(hdc, x, y, x + 30, y+30);
	else
		Rectangle(hdc, x + 30, y + 30, x, y);

	SelectObject(hdc, hOrg);
	DeleteObject(hb);

}

int Car::getX()
{
	return this->x;
}

int Car::getY()
{
	return this->y;
}


void Car::Move()
{
	if (direction)
	{ 
		if (rev)
		{
			x -= 10;
		}
		else
		{
			x += 10;
		}
			
	}
	else
		if (rev)
		{
			y -= 10;
		}
		else
		{
			y += 10;
		}
		
}