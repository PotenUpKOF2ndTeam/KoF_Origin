#include "UI.h"
#include "Image.h"
#include "Character.h"

void UI::Init()
{
	pos = { 0.0f, 0.0f };
	BackGround_Image = new Image();
	if (FAILED(BackGround_Image->Init_2(TEXT("Image/KoF_BackGround.bmp"), 1080, 25000, 1, 50)))
	{
		MessageBox(g_hWnd, TEXT("Image/KoF_BackGround.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	TimeUI1_Image = new Image();
	if (FAILED(TimeUI1_Image->Init_2(TEXT("Image/Timeset2.bmp"), 300, 32, 6, 1,
		true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, TEXT("Image/Timeset2.bmp파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	TimeUI2_Image = new Image();
	if (FAILED(TimeUI2_Image->Init_2(TEXT("Image/Timeset1.bmp"), 510, 32, 10, 1,
		true, RGB(0, 0, 0))))
	{
		MessageBox(g_hWnd, TEXT("Image/Timeset1.bmp파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	elapsedFrame = 0;
	currAnimaionFrame = 0;

	timelEapsedFrame1 = 0;
	timeFrame1 = 0;

	timelEapsedFrame1 = 0;
	timeFrame2 = 0;

	displayedHP = 100;
	maxHP = 100;

	roundCount = 0;

}

void UI::Release()
{
	if (BackGround_Image)
	{
		BackGround_Image->Release();
		delete BackGround_Image;
		BackGround_Image = nullptr;
	}
	if (TimeUI1_Image)
	{
		TimeUI1_Image->Release();
		delete TimeUI1_Image;
		TimeUI1_Image = nullptr;
	}
	if (TimeUI2_Image)
	{
		TimeUI2_Image->Release();
		delete TimeUI2_Image;
		TimeUI2_Image = nullptr;
	}
}

void UI::Update()
{
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE))
	{
		StartUI();
	}

	elapsedFrame++;
	currAnimaionFrame = elapsedFrame;
	if (currAnimaionFrame > 50)
	{
		currAnimaionFrame = 0;
		elapsedFrame = 0;
	}

	if (roundCount == 1)
	{
		timelEapsedFrame2++;
		timeFrame2 = timelEapsedFrame2 / 30;
		if (timeFrame2 > 9)
		{
			timeFrame2 = 0;
			timelEapsedFrame2 = 0;
		}

		timelEapsedFrame1++;
		timeFrame1 = timelEapsedFrame1 / 300;
		if (timeFrame1 > 5)
		{
			timeFrame1 = 0;
			timelEapsedFrame1 = 0;
			roundCount = 2;
		}
	}
}

COLORREF GetHPColor(int hp, int maxHP) {
	float ratio = (float)hp / maxHP;
	int red = (1.0f - ratio) * 255;
	int green = ratio * 255;
	return RGB(red, green, 0);
}

void UI::Render(HDC hdc)
{
	if (BackGround_Image)
	   	BackGround_Image->backRender(hdc, pos.x, pos.y, currAnimaionFrame, false);
}

void UI::StartUI()
{
	roundCount = 1;
}


void UI::HPUI_Render(HDC hdc, int x, int y, int width, int height, int HP, int getDamage, bool isAttak)
{
	// 배경 바 (회색)
	HBRUSH bgBrush = CreateSolidBrush(RGB(50, 50, 50));
	RECT bgRect = { x, y, x + width, y + height };
	FillRect(hdc, &bgRect, bgBrush);
	DeleteObject(bgBrush);

	// HP 바 (색상 변화)
	COLORREF hpColor = GetHPColor(HP, maxHP);
	HBRUSH hpBrush = CreateSolidBrush(hpColor);
	RECT hpRect = { x, y, x + (width * HP / maxHP), y + height };
	FillRect(hdc, &hpRect, hpBrush);
	DeleteObject(hpBrush);
}

void UI::TimeUI1(HDC hdc, int x, int y)
{
	if (TimeUI1_Image)
		TimeUI1_Image->Render_set(hdc, x, y, timeFrame1, false);
}

void UI::TimeUI2(HDC hdc, int x, int y)
{
	if (TimeUI2_Image)
		TimeUI2_Image->Render_set(hdc, x, y, timeFrame2, false);
}

UI::UI()
{
}

UI::~UI()
{
}
