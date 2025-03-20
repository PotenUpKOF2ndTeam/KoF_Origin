#pragma once
#include "GameObject.h"

class Image;
class UI : public GameObject
{
private:
	FPOINT pos;
	Image* UI_Image;
	int elapsedFrame;
	int currAnimaionFrame;	// 0 ~ 8

	int maxHP;
	int currentHP;
	int displayedHP;
	bool isReducing = true;  // HP가 계속 줄어들도록 설정


public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void HPUI_Render(HDC hdc, int x, int y, int width, int height);
	void TimeUI_Render(HDC hdc, int x, int y);


	UI();
	~UI();
};

