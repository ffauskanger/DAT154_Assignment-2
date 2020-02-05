#pragma once

class Car
{
private:
	int id;
	int x;
	int y;
	bool direction;
	bool rev;

public:
	Car(bool direction, bool reverse, int x_val, int y_val);
	void Draw(HDC hdc);
	int getX();
	int getY();
	void Move();
};