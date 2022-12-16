#pragma once
#include "CGame.h"
#include "CVehicle.h"
#include "Point.h"
#include "CAnimal.h"
#include<vector>
class CPeople
{
private:
	Point pos;
	bool mState;
	int length;
public:
	CPeople() 
	{
		mState = true;
		pos.x = 0;
		pos.y = 0;
		length = 3;
		this->mState = true;
	}
	CPeople(int x, int y)
	{
		mState = true;
		pos.x = x;
		pos.y = y;
		length = 3;
		this->mState = true;
	}
	void setState(bool s)
	{
		this->mState = true;
	}
	Point getPos()
	{
		return pos;
	}
	void setPos(int x, int y)
	{
		this->pos.x = x;
		this->pos.y = y;
	}
	void Up()
	{
		if (this->pos.y == 1)
			return;
		this->pos.y--;
		//tell();
	}
	void Down() {
		if (this->pos.y == 45)
			return;
		this->pos.y++;
		//tell();
	}
	void Left() {
		if (this->pos.x == 20)
			return;
		this->pos.x--;
		//tell();
	}
	void Right() {
		if (this->pos.x == 149)
			return;
		this->pos.x++;
		//tell();
	}
	bool isImpact(const vector<CCar> &obj)
	{
		for (int i = 0; i < obj.size(); i++)
		{
			Point p = obj[i].getPos();
			int x1 = p.x;
			int x2 = x1 + obj[0].getLength();
			int y1 = p.y;
			int y2 = y1 + obj[i].getHeight();
			if ((pos.y > y1 && pos.y < y2) || (pos.y + 3 > y1 && pos.y + 3 < y2))
				if ((pos.x > x1 && pos.x < x2) || (pos.x + length > x1 && pos.x + length < x2))
					return true;
		}
		return false;
	}
	bool isImpact(const vector<CTruck>& obj)
	{
		for (int i = 0; i < obj.size(); i++)
		{
			Point p = obj[i].getPos();
			int x1 = p.x;
			int x2 = x1 + obj[0].getLength();
			int y1 = p.y;
			int y2 = y1 + obj[i].getHeight();
			if ((pos.y > y1 && pos.y < y2) || (pos.y + 3 > y1 && pos.y + 3 < y2))
				if ((pos.x > x1 && pos.x < x2) || (pos.x + length > x1 && pos.x + length < x2))
					return true;
		}
		return false;
	}

	bool isImpact(const vector<CBird>& obj)
	{
		for (int i = 0; i < obj.size(); i++)
		{
			Point p = obj[i].getPos();
			int x1 = p.x;
			int x2 = x1 + obj[0].getLength();
			int y1 = p.y;
			int y2 = y1 + obj[i].getHeight();
			if ((pos.y > y1 && pos.y < y2) || (pos.y + 3 > y1 && pos.y + 3 < y2))
				if ((pos.x > x1 && pos.x < x2) || (pos.x + length > x1 && pos.x + length < x2))
					return true;
		}
		return false;
	}
	bool isImpact(const vector<CDinausor>& obj)
	{
		for (int i = 0; i < obj.size(); i++)
		{
			Point p = obj[i].getPos();
			int x1 = p.x;
			int x2 = x1 + obj[0].getLength();
			int y1 = p.y;
			int y2 = y1 + obj[i].getHeight();
			if ((pos.y > y1 && pos.y < y2) || (pos.y + 3 > y1 && pos.y + 3 < y2))
				if ((pos.x > x1 && pos.x < x2) || (pos.x + length > x1 && pos.x + length < x2))
					return true;
		}
		return false;
	}
	
	bool isFinish()
	{
		return pos.y == 2;
	}
	bool isDead()
	{
		return mState == 0;
	}
	void draw(ConsoleHandle &handle)
	{
		handle.drawGraphic(pos.x, pos.y, "HumanTexture.txt");
	}
	void drawDeathEffect(ConsoleHandle& handle) {
		string filePrefixName = "HumanTextureDeath-0";
		for (int i = 1; i <= 2; i++) {
			string fileName = filePrefixName + char(i + 48) + ".txt";
			Sleep(500);
			handle.drawGraphic(pos.x, pos.y, fileName);
		}
	}
	void deletePeople(ConsoleHandle& handle)
	{
		handle.deleteGraphic(pos.x, pos.y,3,length);
	}
	void tell()
	{
		PlaySound(TEXT("sound/moving.wav"), NULL, SND_FILENAME);
	}
};