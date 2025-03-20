#include "Character.h"
#include "Image.h"

void Character::Init(PLAYER playerType)
{
	weakDamage = 10;
	strongDamage = 15;
	HP = 100;
	damage = 0;
	pos = { 0,0 };
	moveSpeed = 5;
	frame = 0;
	currAnimationFrame = 0;
	elapsedFrame = 0;
	maxAnimationFrame = 0;

	isIdle = false;
	isMoveRight = false;
	isMoveLeft = false;
	isWeakPunch = false;
	isStrongPunch = false;
	isWeakKick = false;
	isStrongKick = false;
	isAttack = false;
	isDefend = false;
	isDead = false;

	player = playerType;

	moveImage = new Image;
	idleImage = new Image;
	weakPunchImage = new Image;
	weakKickImage = new Image;
	strongPunchImage = new Image;
	strongKickImage = new Image;

}

void Character::Release()
{
	if (moveImage)
	{
		moveImage->Release();
		delete moveImage;
		moveImage = nullptr;
	}

}

void Character::Update(HDC hdc, int frame)
{
	elapsedFrame++;
	this->frame = frame;

	/*if (isWeakPunch)
	{
		punch();
		return;
	}*/

	if (InputManager::IsPlayerMoveRight(player)
		&& !isWeakPunch && !isWeakKick && !isStrongPunch && !isStrongKick)
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

	if (InputManager::IsPlayerMoveLeft(player) && !isWeakPunch && !isWeakKick && !isStrongPunch && !isStrongKick)
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
		
	if (InputManager::IsPlayerAttackWeakPunch(player))
	{
		isWeakPunch = true;
		maxAnimationFrame = 10;
		currAnimationFrame++;		
		
		Attack();

		currAnimationFrame %= maxAnimationFrame; // currAnimationFrame = currAnimationFrame % 10
		if (currAnimationFrame == maxAnimationFrame)
		{
			isWeakPunch = false;
		}
	}
	else {
		isWeakPunch = false;
	}

	if (InputManager::IsPlayerAttackWeakKick(player))
	{
		isWeakKick = true;
		maxAnimationFrame = 10;
		currAnimationFrame++;

		Attack();

		currAnimationFrame++;
		currAnimationFrame %= maxAnimationFrame; // currAnimationFrame = currAnimationFrame % 10
		if (currAnimationFrame == maxAnimationFrame)
		{
			isWeakKick = false;
		}
	}
	else {
		isWeakKick = false;
	}


	if (InputManager::IsPlayerAttackStrongPunch(player))
	{
		isStrongPunch = true;
		maxAnimationFrame = 10;
		currAnimationFrame++;

		Attack();

		currAnimationFrame++;
		currAnimationFrame %= maxAnimationFrame; // currAnimationFrame = currAnimationFrame % 10
		if (currAnimationFrame == maxAnimationFrame)
		{
			isStrongPunch = false;
		}
	}
	else {
		isStrongPunch = false;
	}

	if (InputManager::IsPlayerAttackStrongKick(player))
	{
		isStrongKick = true;
		maxAnimationFrame = 10;
		currAnimationFrame++;

		Attack();

		currAnimationFrame++;
		currAnimationFrame %= maxAnimationFrame; // currAnimationFrame = currAnimationFrame % 10
		if (currAnimationFrame == maxAnimationFrame)
		{
			isStrongKick = false;
		}
	}
	else {
		isStrongKick = false;
	}
}

void Character::Render(HDC hdc)
{	
	if (isMoveLeft || isMoveRight)
	{
		moveImage->Render(hdc, pos.x, pos.y, currAnimationFrame, false);
	}
	else if (isWeakPunch)
	{
		weakPunchImage->Render(hdc, pos.x, pos.y, currAnimationFrame, false);
	}
	else if (isWeakKick)
	{
		weakKickImage->Render(hdc, pos.x, pos.y, currAnimationFrame, false);
	}
	else if (isStrongPunch)
	{
		strongPunchImage->Render(hdc, pos.x, pos.y, currAnimationFrame, false);
	}
	else if (isStrongKick)
	{
		strongKickImage->Render(hdc, pos.x, pos.y, currAnimationFrame, false);
	}
	else 
		idleImage->Render(hdc, pos.x, pos.y, currAnimationFrame, false);

}

void Character::Move()
{
	// right 할 때 
	if (isMoveRight)
	{
		pos.x += moveSpeed;
	}

	// left 할 때 
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

void Character::Attack()
{
	if (currAnimationFrame == 3)
	{
		isAttack = true;
		damage = 4;
	}
	else
	{
		isAttack = false;
		damage = 0;
	}
}

void Character::Punch()
{
	if (currAnimationFrame == 3)
	{
		isAttack = true;
		damage = 4;
	}
	else
	{
		isAttack = false;
		damage = 0;
	}

	currAnimationFrame++;
	currAnimationFrame %= 10; // currAnimationFrame = currAnimationFrame % 10
	if (currAnimationFrame == maxAnimationFrame)
	{
		isWeakPunch = false;
	}
}

void Character::SetImage(const wchar_t* filePath , int width, int height, int maxAnimationFrame)
{

	if (FAILED(moveImage->Init(TEXT("Image/Clark_3800x1200_200x200.bmp"), 612, 104, maxAnimationFrame, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/iori_walk.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	
	moveImage-> 
	this->maxAnimationFrame = maxAnimationFrame; 
}

Character::Character()
{
}

Character::~Character()
{
}
