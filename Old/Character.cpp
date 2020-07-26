#include "stdafx.h"
#include "Character.h"


Character::Character()
{
	inTheArea = true;
	myPos = { 0 , 0 };
}


Character::~Character()
{
}

bool Character::PlusPos(POINT movePt)
{
	if ((myPos.x + movePt.x >= 1) && (myPos.x + movePt.x < gameSize-1) && 
		(myPos.y + movePt.y >= 1) && (myPos.y + movePt.y < gameSize-1))
	{
		myPos.x += movePt.x;
		myPos.y += movePt.y;
		return true;
	}
	return false;
}

void Character::SetPos(POINT movePt)
{
	myPos = movePt;
}

POINT Character::GetPos()
{
	return myPos;
}

void Character::Draw(HDC hdc)
{
	Rectangle(hdc, myPos.x * pixelSize , myPos.y * pixelSize, myPos.x * pixelSize + mySize, myPos.y * pixelSize + mySize);
}

void Character::Update()
{
	
}

void Character::SetInTheArea(bool in)
{
	inTheArea = in;
}
