#pragma once
#include "GameObject.h"
#include "Character.h"
#include "UI.h"	

class Image;
class KOF_Iori;
class HitDetection;
class MainGame : public GameObject
{
private:
	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;
	int mousePosX = 0, mousePosY = 0;
	FPOINT mousePos;
	wchar_t szText[128];

	bool gameStarted = false;
	Image* backBuffer;
	Image* backGround;

	Image* GameStartImg;
	Character* player1;
	Character* player2;

	int player1_HP;
	int player1_Damage;
	int player2_HP;
	int player2_Damage;

	bool player1_isAttak = false;
	bool player2_isAttak = false;

	UI* Ui;


	HitDetection* replication;
public:
	void PreInit();
	void Init();	// override (부모클래스와 같은 함수이름, 로직을 다르게 구현하고 싶을 때)
					// <-> overload (같은 함수 이름, 매개변수 타입과 갯수가 다르면 다른 함수로 처리)
	void Release();	
	void Update();	
	void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

