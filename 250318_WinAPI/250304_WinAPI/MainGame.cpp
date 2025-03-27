#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "KOF_Iori.h"
#include "HitDetection.h"

void MainGame::PreInit()
{
	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("백버퍼 생성 실패"), TEXT("경고"), MB_OK);
	}
}

void MainGame::Init()
{

	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("백버퍼 생성 실패"), TEXT("경고"), MB_OK);
	}

	player1 = new Character();
	player1->Init(PLAYER::Player1);
	player1->SetImage(TEXT("Image/Clark_3800x1200_200x200.bmp"), 3800, 1200, 18, 7, 5, 8, 4, 16);

	player2 = new Character();
	player2->Init(PLAYER::Player2);
	player2->SetImage(TEXT("Image/Mai_2400x1200_200x200.bmp"), 2400, 1200, 12, 6, 4, 5, 6, 6);

	replication = new HitDetection();
	replication->Init();
	replication->Replication(player1, player2);

	Ui = new UI();
	Ui->Init();

	player1_HP = 0;
	player1_Damage = 0;

	player2_HP = 0;
	player2_Damage = 0;


}

void MainGame::Release()
{
	if (player1)
	{
		player1->Release();
		delete player1;
		player1 = nullptr;
	}

	if (player2)
	{
		player2->Release();
		delete player2;
		player2 = nullptr;
	}

	if (backBuffer)
	{
		backBuffer->Release();
		delete backBuffer;
		backBuffer = nullptr;
	}

	if (replication)
	{
		replication->Release();
		delete replication;
		replication = nullptr;
	}

	if (Ui)
	{
		Ui->Release();
		delete Ui;
		Ui = nullptr;
	}
}

void MainGame::Update()
{
	if (player1)
	{
		player1->Update();
		player1_HP = player1->GetHP();
		player1_Damage = player2->GetDamage();
		player1_isAttak = player1->GetIsAttack();
	}

	if (player2)
	{
		player2->Update();
		player2_HP = player2->GetHP();
		player2_Damage = player1->GetDamage();
		player2_isAttak = player2->GetIsAttack();
	}

	if (Ui)
		Ui->Update();

	if (replication) {
		replication->Update();
	}

	if (player1_HP <= 0)
	{
		player1_HP = 0;
		DestroyWindow(g_hWnd);
	}

	if (player2_HP <= 0)
	{
		player2_HP = 0;
		DestroyWindow(g_hWnd);
	}

	if (Ui && Ui->GetRoundCount() == 2)
	{
		DestroyWindow(g_hWnd);
	}
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	// 백버퍼에 먼저 복사
	HDC hBackBufferDC = backBuffer->GetMemDC();

	if (Ui && Ui->GetRoundCount() == 0) {
		
		Ui->Start_Render(hBackBufferDC);
	}

	if (Ui && Ui->GetRoundCount() == 1) {
		Ui->Render(hBackBufferDC);
		Ui->TimeUI1(hBackBufferDC, WINSIZE_X / 2 - 34, 50);
		Ui->TimeUI2(hBackBufferDC, WINSIZE_X / 2 + 17, 50);
		Ui->HPUI_Render(hBackBufferDC, WINSIZE_X - 1040, 30, 300, 50, player1_HP, player1_Damage, player1_isAttak);
		Ui->HPUI_Render(hBackBufferDC, WINSIZE_X - 340, 30, 300, 50, player2_HP, player2_Damage, player2_isAttak);
	}
	if (Ui && Ui->GetRoundCount() == 1)
	{
		if (player1) player1->Render(hBackBufferDC);
		if (player2) player2->Render(hBackBufferDC);
	}
	// 백버퍼에 있는 내용을 메인 hdc에 복사
	backBuffer->Render(hdc);

}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		hTimer = (HANDLE)SetTimer(hWnd, 0, 50, NULL);

		break;
	case WM_TIMER:
		this->Update();
		break;
	case WM_KEYUP:
		break;
	case WM_KEYDOWN:
		break;
	case WM_LBUTTONDOWN:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		mousePos.x = LOWORD(lParam);
		mousePos.y = HIWORD(lParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);

		this->Render(hdc);

		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 0);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}
