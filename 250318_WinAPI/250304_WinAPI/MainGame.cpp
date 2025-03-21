#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "KOF_Iori.h"
#include "HitDetection.h"

/*
	실습1. 이오리 집에 보내기
	실습2. 배경 바꾸기 (킹오파 애니메이션 배경)
*/

void MainGame::PreInit()
{
	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("백버퍼 생성 실패"), TEXT("경고"), MB_OK);
	}

	backGround = new Image();
	if (FAILED(backGround->Init(TEXT("Image/background.bmp"), WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/backGround.bmp 생성 실패"), TEXT("경고"), MB_OK);
	}

	GameStartImg = new Image();
	if (FAILED(GameStartImg->Init(TEXT("Image/pressstart.bmp"), WINSIZE_X - 100, WINSIZE_Y - 100)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/pressstart.bmp 생성 실패"), TEXT("경고"), MB_OK);
	}

	replication = new HitDetection();

	replication->Init();

}

void MainGame::Init()
{
	if (GameStartImg)
	{
		GameStartImg->Release();
		delete GameStartImg;
		GameStartImg = nullptr;
	}

	player1 = new Character();
	player1->Init(PLAYER::Player1);

	player1->SetImage(TEXT("Image/Clark_3800x1200_200x200.bmp"), 3800, 1200, 18, 7, 5, 8, 4, 16);

	player2 = new Character();
	player2->Init(PLAYER::Player2);
  player2->SetImage(TEXT("Image/Mai_2400x1200_200x200.bmp"), 2400, 1200, 12, 6, 4, 5, 6, 6);
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

	if (backGround)
	{
		backGround->Release();
		delete backGround;
		backGround = nullptr;
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
	}

	if (player2_HP <= 0)
	{
		player2_HP = 0;
	}
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	// 백버퍼에 먼저 복사
	HDC hBackBufferDC = backBuffer->GetMemDC();

	if (backGround) backGround->Render(hBackBufferDC);
	if (GameStartImg)
	{
		GameStartImg->Render(hBackBufferDC, 50, 20);
		wsprintf(szText, TEXT("Press Enter to Start the Game"));
		TextOut(hBackBufferDC, WINSIZE_X * (2.0f / 5.0f), WINSIZE_Y - 70, szText, wcslen(szText));
	}
	if (player1) player1->Render(hBackBufferDC);
	if (player2) player2->Render(hBackBufferDC);

	if (Ui) {
		Ui->Render(hBackBufferDC);
		Ui->TimeUI1(hBackBufferDC, WINSIZE_X / 2 - 34, 50);
		Ui->TimeUI2(hBackBufferDC, WINSIZE_X / 2 + 17, 50);
		Ui->HPUI_Render(hBackBufferDC, WINSIZE_X - 1040, 30, 300, 50, player1_HP, player1_Damage, player1_isAttak);
		Ui->HPUI_Render(hBackBufferDC, WINSIZE_X - 340, 30, 300, 50, player2_HP, player2_Damage, player2_isAttak);
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
		KeyManager::GetInstance()->SetKeyDown(wParam, false);
		KeyManager::GetInstance()->SetKeyUp(wParam, true);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_RETURN && gameStarted == false)
			Init();
		KeyManager::GetInstance()->SetKeyDown(wParam, true);
		KeyManager::GetInstance()->SetKeyUp(wParam, false);
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
