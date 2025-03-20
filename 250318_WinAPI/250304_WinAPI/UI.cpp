#include "UI.h"
#include "Image.h"

void UI::Init()
{
	pos = { 0.0f, 0.0f };

	elapsedFrame = 0;
	currAnimaionFrame = 0;

	displayedHP = 100;
	maxHP = 100;
	currentHP = 100;

}

void UI::Release()
{
	if (UI_Image)
	{
		UI_Image->Release();
		delete UI_Image;
		UI_Image = nullptr;
	}
}

void UI::Update()
{
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE))
	{
		if (currentHP > 0) {
			currentHP -= 1;  // 자동으로 HP 감소
		}
	}
}

// HP 바 색상 계산 (초록 -> 노랑 -> 빨강)
COLORREF GetHPColor(int hp, int maxHP) {
	float ratio = (float)hp / maxHP;
	int red = (1.0f - ratio) * 255;
	int green = ratio * 255;
	return RGB(red, green, 0);
}


void UI::Render(HDC hdc)
{
	if (UI_Image)
		UI_Image->Render(hdc, pos.x, pos.y, currAnimaionFrame, true);
}

void UI::HPUI_Render(HDC hdc, int x, int y, int width, int height)
{

	// HP 애니메이션 적용 (점진적 감소)
	if (displayedHP > currentHP) {
		displayedHP -= 1;
	}

	// 배경 바 (회색)
	HBRUSH bgBrush = CreateSolidBrush(RGB(50, 50, 50));
	RECT bgRect = { x, y, x + width, y + height };
	FillRect(hdc, &bgRect, bgBrush);
	DeleteObject(bgBrush);

	// HP 바 (색상 변화)
	COLORREF hpColor = GetHPColor(displayedHP, maxHP);
	HBRUSH hpBrush = CreateSolidBrush(hpColor);
	RECT hpRect = { x, y, x + (width * displayedHP / maxHP), y + height };
	FillRect(hdc, &hpRect, hpBrush);
	DeleteObject(hpBrush);
}


UI::UI()
{
}

UI::~UI()
{
}
