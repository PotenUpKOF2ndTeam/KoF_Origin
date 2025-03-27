#pragma once
#include "GameObject.h"

class Image;
class UI
{
private:
	FPOINT pos;
	Image* Start_BackGround_Image;
	Image* BackGround_Image;
	Image* TimeUI1_Image;
	Image* TimeUI2_Image;

	int startElapsedFrame;
	int startFrame;
	int elapsedFrame;
	int currAnimaionFrame;
	int timelEapsedFrame1;
	int timeFrame1;
	int timelEapsedFrame2;
	int timeFrame2;

	int roundCount;

	int maxHP;
	int displayedHP;
	bool isReducing = true;  // HP가 계속 줄어들도록 설정

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void Start_Render(HDC hdc);
	void StartUI();
	void HPUI_Render(HDC hdc, int x, int y, int width, int height, int HP, int getDamage, bool isAttak);
	void TimeUI1(HDC hdc, int x, int y);
	void TimeUI2(HDC hdc, int x, int y);

	int GetRoundCount() { return roundCount; };

	UI();
	~UI();
};
