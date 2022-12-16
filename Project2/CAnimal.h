#pragma once
#include "CGame.h"
#include "Point.h"
#include "vector"
#include"CTrafficLight.h"
#include "ConsoleHandle.h"

class CAnimal
{
protected:
	Point pos;
	bool direction;
public:
	CAnimal()
	{
		pos.x = 0;
		pos.y = 0;
		direction = 0;
	}
	CAnimal(int x, int y)
	{
		pos.x = x;
		pos.y = y;
		direction = 0;
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
	void setDirection(bool direction)
	{
		this->direction = direction;
	}
	void Move()
	{
		pos.x--;
	}
	void deleteAnimal(ConsoleHandle& handle)
	{
		if (pos.x == 20+13)
		{
			handle.deleteGraphic(pos.x, pos.y, getHeight(), getLength()+1);
			return;
		}
		handle.deleteGraphic(pos.x + getLength(), pos.y, getHeight(), 1);
	}
	virtual void Tell() = 0;
	virtual int getLength() const = 0;
	virtual int getHeight() const = 0;
};

class CBird : public CAnimal
{
private:
	int length;
	int height;
public:
	CBird() : CAnimal(0, 0) {
		this->length = 12;
		this->height = 6;
	}
	CBird(int x, int y) : CAnimal(x, y)
	{
		this->height = 6;
		this->length = 12;
	}
	CBird(const CBird& car)
	{
		this->height = 6;
		this->length = 12;
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
	void drawBird(ConsoleHandle& handle)
	{
		handle.drawGraphic(pos.x, pos.y, "BirdTexture.txt",246);
	}
};

class CDinausor : public CAnimal
{
private:
	int length;
	int height;
public:
	CDinausor() : CAnimal(0, 0) {
		this->height = 6;
		this->length = 18;
	}
	CDinausor(int x, int y) : CAnimal(x, y)
	{
		this->height = 6;
		this->length = 18;
	}
	CDinausor(const CDinausor& truck)
	{
		this->height = 6;
		this->length = 18;
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
		PlaySound(TEXT("sound/dinausor.wav"), NULL, SND_FILENAME);
	}
	void drawDinausor(ConsoleHandle& handle)
	{
		handle.drawGraphic(pos.x, pos.y, "DinausorTexture.txt",245);
	}
};