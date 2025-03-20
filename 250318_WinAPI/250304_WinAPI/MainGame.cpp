#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "KOF_Iori.h"

/*
	�ǽ�1. �̿��� ���� ������
	�ǽ�2. ��� �ٲٱ� (ŷ���� �ִϸ��̼� ���)
*/

void MainGame::PreInit()
{
	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("����� ���� ����"), TEXT("���"), MB_OK);
	}

	backGround = new Image();
	if (FAILED(backGround->Init(TEXT("Image/background.bmp"), WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/backGround.bmp ���� ����"), TEXT("���"), MB_OK);
	}

	GameStartImg = new Image();
	if (FAILED(GameStartImg->Init(TEXT("Image/pressstart.bmp"), WINSIZE_X - 100, WINSIZE_Y - 100)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/pressstart.bmp ���� ����"), TEXT("���"), MB_OK);
	}
}

void MainGame::Init()
{
	if (GameStartImg)
	{
		GameStartImg->Release();
		delete GameStartImg;
		GameStartImg = nullptr;
	}

	iori = new KOF_Iori();
	iori->Init();
}

void MainGame::Release()
{
	if (iori)
	{
		iori->Release();
		delete iori;
		iori = nullptr;
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
}

void MainGame::Update()
{
	if (iori)
		iori->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	// ����ۿ� ���� ����
	HDC hBackBufferDC = backBuffer->GetMemDC();

	if (backGround) backGround->Render(hBackBufferDC);
	if (GameStartImg)
	{
		GameStartImg->Render(hBackBufferDC, 50, 20);
		wsprintf(szText, TEXT("Press Enter to Start the Game"));
		TextOut(hBackBufferDC, WINSIZE_X * (2.0f / 5.0f), WINSIZE_Y - 70, szText, wcslen(szText));
	}
	if (iori) iori->Render(hBackBufferDC);

	// ����ۿ� �ִ� ������ ���� hdc�� ����
	backBuffer->Render(hdc);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		hTimer = (HANDLE)SetTimer(hWnd, 0, 10, NULL);

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
