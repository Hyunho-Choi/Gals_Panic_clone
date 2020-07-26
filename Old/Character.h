#pragma once
const static int pixelSize = 10;
const static int gameSize = 50;

class Character
{
private :
	POINT myPos;
	const int mySize = pixelSize;
	int turnCount = 0;
	
public:
	bool inTheArea;

	Character();
	~Character();
	bool PlusPos(POINT movePt);
	void SetPos(POINT movePt);
	POINT GetPos();
	void Draw(HDC hdc);
	void Update();
	void SetInTheArea(bool in);
	

};

