#pragma once
#include "Character.h"

//const static int pixelSize = 20;
const static int moveSpeed = 1;

class GameManager
{
private:
	int map[gameSize][gameSize];
	HBRUSH oldBrush, myAreaBrush, newLineBrush, charaBrush, blankBrush;
	HPEN oldPen, myAreaPen , newLinePen, blankPen;
	Character mainChara;
	int startPos;
	POINT scan[2];

public:
	GameManager();
	~GameManager();
	short GetPixel(POINT pt);
	void ToMyArea(POINT newPt);
	void Controller(WPARAM wParam);
	void Draw(HDC hdc);
	void Update();
	void FloodFill();
	void SetMyArea();
	bool InsideScanner(POINT* scan);
	void FloodFill(POINT change, int scan);
	void changeNewLine(POINT start);
};

