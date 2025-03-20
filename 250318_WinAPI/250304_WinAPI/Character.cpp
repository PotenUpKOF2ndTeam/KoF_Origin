#include "Character.h"
#include "Image.h"

void Character::Init(PLAYER playerType)
{
	weakDamage = 10;
	strongDamage = 15;
	HP = 100;
	pos = { 0,0 };
	moveSpeed = 5;
	frame = 0;
	currAnimationFrame = 0.0f;
	elapsedFrame = 0.0f;

	isMoveRight = false;
	isMoveLeft = false;
	isWeakPunch = false;
	isStrongPunch = false;
	isWeakKick = false;
	isStrongKick = false;
	isDefend = false;
	isDead = false;
	
	player = playerType;

	image = new Image;
	if (FAILED(image->Init(TEXT("Image/iori_walk.bmp"), 612, 104, 9, 1,
		true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/iori_walk.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}

	
}

void Character::Release()
{
	if (image)
	{
		image->Release();
		delete image;
		image = nullptr;
	}

}

void Character::Update(int frame)
{
	elapsedFrame++;
	this->frame = frame;

	if (InputManager::IsPlayer1MoveRight())
	{
		isMoveRight = true;
		currAnimationFrame++;
		Move();
		if (currAnimationFrame > frame)
		{
			currAnimationFrame = 0;
		}
		elapsedFrame = 0;
	}
	else
	{
		isMoveRight = false;
	}

	if (InputManager::IsPlayer1MoveLeft())
	{
		isMoveLeft = true;
		currAnimationFrame++;
		Move();
		if (currAnimationFrame > frame)
		{
			currAnimationFrame = 0;
		}
		elapsedFrame = 0;

	}
	else {
		isMoveLeft = false;
	}

	if (InputManager::IsPlayer2MoveRight())
	{
		isMoveRight = true;
		currAnimationFrame++;
		Move();
		if (currAnimationFrame > frame)
		{
			currAnimationFrame = 0;
		}
		elapsedFrame = 0;
	}
	else {
		isMoveRight = false;
	}

	if (InputManager::IsPlayer2MoveLeft())
	{
		isMoveLeft = true;
		currAnimationFrame++;
		Move();
		if (currAnimationFrame > frame)
		{
			currAnimationFrame = 0;
		}
		elapsedFrame = 0;
	}
	else {
		isMoveLeft = false;
	}
}

void Character::Render(HDC hdc)
{
	//�̹��� ����
	if (player == PLAYER::Player1)
	{
		image->Render(hdc, pos.x, pos.y, currAnimationFrame, false);
	}

	else if (player == PLAYER::Player2)
	{
		image->Render(hdc, pos.x + 300, pos.y, currAnimationFrame, true);
	} 

	//����

	//����ġ 

	//����ġ

	//��ű

	//��ű
}

void Character::Move()
{
	// right �� �� 
	if (isMoveRight)
	{
		pos.x += moveSpeed;
	}

	// left �� �� 
	if (isMoveLeft)
	{
		pos.x -= moveSpeed;
	}

}

void Character::OnDamaged(int damage)
{
	HP -= damage;
	if (HP <= 0)
	{
		Dead();
	}
}

void Character::Dead()
{
	isDead = true;
}

Character::Character()
{
}

Character::~Character()
{
}
