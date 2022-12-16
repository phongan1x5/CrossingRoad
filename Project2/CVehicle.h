#pragma once
#include "CGame.h"
#include "Point.h"
#include "vector"
#include"CTrafficLight.h"
#include "ConsoleHandle.h"

class CVehicle
{
protected:	
	Point pos;
	bool direction;
public:
	CVehicle()
	{
		pos.x = 0;
		pos.y = 0;
		direction = 1;
	}
	CVehicle(int x, int y)
	{
		pos.x = x;
		pos.y = y;
		direction = 1;
	}
	Point getPos() const
	{
		return pos;
	}
	void setPos(int x, int y)
	{
		this->pos.x = x;
		this->pos.y = y;
	}
	bool getDirection() const
	{
		return direction;
	}
	void setDirection(bool direc)
	{
		this->direction = direc;
	}
	void Move(TrafficLight lightList)
	{
		if (lightList.getStatus() == "Light-2.txt")
			return;
		pos.x++;
	}
	void deleteVehicle(ConsoleHandle& handle, TrafficLight lightList)
	{
		if (pos.x == 151 + 12 - getLength())
		{
			handle.deleteGraphic(pos.x-1, pos.y, getHeight(), getLength()+1);
			return;
		}
		handle.deleteGraphic(pos.x-1, pos.y, getHeight(), 1);
	}
	virtual void Tell() = 0;
	virtual int getLength() const = 0;
	virtual int getHeight() const = 0;
};

class CCar : public CVehicle
{
private:
	int length;
	int height;
public:
	CCar() : CVehicle(0, 0) 
	{
		this->length = 21; 
		this->height = 4;
		direction = 1;
	}
	CCar(int x, int y) : CVehicle(x, y)
	{
		this->height = 4;
		this->length = 21;
		direction = 1;
	}
	CCar(const CCar& car)
	{
		this->height = 4;
		this->length = 21;
		this->pos = car.pos;
		this->direction = car.direction;
	}
	int getLength() const
	{
		return length;
	}
	int getHeight() const
	{
		return height;
	}
	void Tell()
	{
		PlaySound(TEXT("sound/bird.wav"), NULL, SND_FILENAME);
	}
	void drawCar(ConsoleHandle &handle)
	{
		handle.drawGraphic(pos.x, pos.y, "CarTexture.txt",241);
	}
};

class CTruck : public CVehicle
{
private:
	int length;
	int height;
public:
	CTruck() : CVehicle(0, 0) {
		this->height = 4;
		this->length = 19; 
	}
	CTruck(int x, int y) : CVehicle(x, y)
	{
		this->height = 4;
		this->length = 19;
	}
	CTruck(const CTruck& truck)
	{
		this->height = 4;
		this->length = 19;
		this->pos = truck.pos;
		this->direction = truck.direction;
	}
	int getLength() const
	{
		return length;
	}
	int getHeight() const
	{
		return height;
	}
	void Tell()
	{
		PlaySound(TEXT("sound/truck.wav"), NULL, SND_FILENAME);
	}
	void drawTruck(ConsoleHandle& handle)
	{
		handle.drawGraphic(pos.x, pos.y, "TruckTexture.txt",242);
	}
};