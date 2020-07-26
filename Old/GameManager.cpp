#include "stdafx.h"
#include "GameManager.h"


GameManager::GameManager()
{
	blankBrush = CreateSolidBrush(RGB(200, 200, 200));
	blankPen = CreatePen(PS_INSIDEFRAME | PS_NULL, 0, RGB(200, 200, 200));

	myAreaBrush = CreateSolidBrush(RGB(0, 255, 0));
	myAreaPen = CreatePen(PS_INSIDEFRAME | PS_NULL, 0, RGB(0, 255, 0));

	newLineBrush = CreateSolidBrush(RGB(255, 255, 0));
	newLinePen = CreatePen(PS_INSIDEFRAME | PS_NULL, 0, RGB(255, 255, 0));

	charaBrush = CreateSolidBrush(RGB(150, 150, 0));



	for (int i = 0; i<gameSize; i++)
		memset(map[i], -1, sizeof(int)* gameSize);

	startPos = gameSize / 2 - 5;
	mainChara.SetPos({ startPos ,startPos});
	
	
	//기본 영역 설정
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			map[(startPos + i)][startPos + j] = 2;
		}
	}
}


GameManager::~GameManager()
{
}

short GameManager::GetPixel(POINT pt)
{
	return map[pt.x][pt.y];
}

void GameManager::ToMyArea(POINT newPt)
{
	map[newPt.x][newPt.y] = 2;
}

void GameManager::Controller(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_LEFT:
		if (mainChara.PlusPos({ -moveSpeed, 0 }) &&
			(map[mainChara.GetPos().x - 1][mainChara.GetPos().y] == 3 ||
			map[mainChara.GetPos().x][mainChara.GetPos().y - 1] == 3 ||
			map[mainChara.GetPos().x][mainChara.GetPos().y + 1] == 3))
				mainChara.PlusPos({ moveSpeed, 0 });
		Update();
		break;
	case VK_UP:
		if (mainChara.PlusPos({ 0, -moveSpeed }) &&
			(map[mainChara.GetPos().x][mainChara.GetPos().y - 1] == 3 ||
			map[mainChara.GetPos().x-1][mainChara.GetPos().y] == 3 ||
			map[mainChara.GetPos().x+1][mainChara.GetPos().y] == 3))
			mainChara.PlusPos({ 0, moveSpeed });
		Update();
		break;
	case VK_RIGHT:
		if (mainChara.PlusPos({ moveSpeed , 0 }) &&
			(map[mainChara.GetPos().x + 1][mainChara.GetPos().y] == 3 ||
			map[mainChara.GetPos().x][mainChara.GetPos().y-1] == 3 ||
			map[mainChara.GetPos().x][mainChara.GetPos().y+1] == 3))
			mainChara.PlusPos({ -moveSpeed , 0 });
		Update();
		break;
	case VK_DOWN:
		if (mainChara.PlusPos({ 0 , moveSpeed }) &&
			(map[mainChara.GetPos().x][mainChara.GetPos().y + 1] == 3 ||
			map[mainChara.GetPos().x - 1][mainChara.GetPos().y] == 3 ||
			map[mainChara.GetPos().x + 1][mainChara.GetPos().y] == 3))
				mainChara.PlusPos({ 0 , -moveSpeed });
		Update();
		break;
	}
	
}

void GameManager::Draw(HDC hdc)
{
	int i,j;
	for (i = 0; i < gameSize; i++)
	{
		for (j = 0; j < gameSize; j++)
		{
			
			switch (map[i][j])
			{
				
			case -1: 
				oldBrush = (HBRUSH)SelectObject(hdc, blankBrush);
				oldPen = (HPEN)SelectObject(hdc, blankPen);
				break;
			case 2:
				oldBrush = (HBRUSH)SelectObject(hdc, myAreaBrush);
				oldPen = (HPEN)SelectObject(hdc, myAreaPen);
				break;
			case 3:
				oldBrush = (HBRUSH)SelectObject(hdc, newLineBrush);
				oldPen = (HPEN)SelectObject(hdc, newLinePen);
				break;
			}
			Rectangle(hdc, i * pixelSize, j * pixelSize, i * pixelSize + pixelSize, j * pixelSize + pixelSize);
			SelectObject(hdc, oldBrush);
		}
	}
	oldBrush = (HBRUSH)SelectObject(hdc, charaBrush);
	mainChara.Draw(hdc);
	SelectObject(hdc, oldBrush);
	SelectObject(hdc, oldPen);
}

void GameManager::Update()
{
	switch (map[mainChara.GetPos().y][mainChara.GetPos().x])
	{
	case -1 : // 영역안에서 나온케이스
		if (mainChara.inTheArea == true)
		{
			scan[0] = { mainChara.GetPos().x , mainChara.GetPos().y-1 };
 		}

		mainChara.inTheArea = false;
		break;
	case 2 : // 영역안에서 움직인 케이스 or 영역 밖에서 안으로 온케이스
		if (mainChara.inTheArea == false)
		{
			InsideScanner(scan);
			// 라인영역과 안쪽을 내 영역으로 재설정
		}
		mainChara.inTheArea = true;
		break;
	case 3 : // 선위에서 움직이는 케이스
		mainChara.inTheArea = false;
		break;
	}

	if (!mainChara.inTheArea)
	{
		map[mainChara.GetPos().x][mainChara.GetPos().y] = 3;
	}
}

bool GameManager::InsideScanner(POINT* scan)
{
	int m_cnt = 0;
	int now = -1;
	POINT storage = scan[0];
	while (scan[0].y > 0)
	{
		if ((map[scan[0].y--][scan[0].x] == 3)&&(now == -1))
		{
			m_cnt++;
		}
		scan[0].y--;
	}
	if ((m_cnt % 2) == 1)
	{
		// 플루드필
		FloodFill(storage, -1);
	}

	return false;
}

void GameManager::FloodFill(POINT change, int scan)
{
	// 선포함?? 미포함? 
	// 재귀?
	map[change.y][change.x] = 2;
	if (map[change.y-1][change.x] == scan)
	{
		FloodFill({ change.x ,change.y - 1 }, scan);
	}
	if (map[change.y + 1][change.x] == scan)
	{
		FloodFill({ change.x ,change.y + 1 }, scan);
	}
	if (map[change.y][change.x-1] == scan)
	{
		FloodFill({ change.x-1 ,change.y }, scan);
	}
	if (map[change.y][change.x+1] == scan)
	{
		FloodFill({ change.x+1 ,change.y }, scan);
	}
	return;
}

void GameManager::changeNewLine(POINT start)
{
	FloodFill(start, 3);
}
