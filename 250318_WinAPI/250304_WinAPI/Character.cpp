#include "Character.h"
#include "Image.h"

void Character::Init(PLAYER playerType)
{
	HP = 100;
	damage = 0;
	pos = { 0,0 };
	moveSpeed = 5;
	currAnimationFrame = 0;
	maxAnimationFrame = 0;

	maxWalkFrame = 0;
	maxWeakPunchFrame = 0;
	maxStrongPunchFrame = 0;
	maxWeakKickFrame = 0;
	maxStrongKickFrame = 0;

	isIdle = false;
	isMoveRight = false;
	isMoveLeft = false;
	isWeakPunch = false;
	isStrongPunch = false;
	isWeakKick = false;
	isStrongKick = false;
	isAttack = false;
	isDead = false;

	player = playerType;

	image = new Image;
	if (playerType == PLAYER::Player1)
	{
		pos = { PLAYER1_START_X, PLAYER_START_Y };
		isFilp = false;
	}
	else
	{
		pos = { PLAYER2_START_X ,PLAYER_START_Y };
		isFilp = true;
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

void Character::Update()
{
	if (isWeakPunch)
		return AttackWeakPunch();

	if (isWeakKick)
		return AttackWeakKick();

	if (isStrongPunch)
		return AttackStrongPunch();

	if (isStrongKick)
		return AttackStrongKick();

	if (InputManager::IsPlayerMoveRight(player))
	{	
		isMoveRight = true;
		Move();
	}
	else
	{
		isMoveRight = false;
	}

	if (InputManager::IsPlayerMoveLeft(player))
	{
		isMoveLeft = true;
		Move();	
	}
	else {
		isMoveLeft = false;
	}
		
	if (InputManager::IsPlayerAttackWeakPunch(player) && !isMoveLeft && !isMoveRight)
	{
		isWeakPunch = true;		
		currAnimationFrame = 0;
	}
	
	if (InputManager::IsPlayerAttackWeakKick(player) && !isMoveLeft && !isMoveRight)
	{
		isWeakKick = true;		
		currAnimationFrame = 0;
	}
	
	if (InputManager::IsPlayerAttackStrongPunch(player) && !isMoveLeft && !isMoveRight)
	{
		isStrongPunch = true;	
		currAnimationFrame = 0;
	}
	
	if (InputManager::IsPlayerAttackStrongKick(player) && !isMoveLeft && !isMoveRight)
	{
		isStrongKick = true;
		currAnimationFrame = 0;
	}
	
}

void Character::Render(HDC hdc)
{		
	if (isMoveLeft || isMoveRight)
	{
		currAnimationFrame %= maxWalkFrame;
		image->Render(hdc, pos.x, pos.y, 1, currAnimationFrame, isFilp);				
	}
	else if (isWeakPunch)
	{
		image->Render(hdc, pos.x, pos.y, 2, currAnimationFrame, isFilp);
	}
	else if (isWeakKick)
	{
		image->Render(hdc, pos.x, pos.y, 4, currAnimationFrame, isFilp);					
	}
	else if (isStrongPunch)
	{
		image->Render(hdc, pos.x, pos.y, 3, currAnimationFrame, isFilp);		
	}
	else if (isStrongKick)
	{
		image->Render(hdc, pos.x, pos.y, 5, currAnimationFrame, isFilp);		
	}
	else
	{
		currAnimationFrame %= maxAnimationFrame;
		image->Render(hdc, pos.x, pos.y, 0, currAnimationFrame, isFilp);		
	}

	currAnimationFrame++;
	
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

void Character::AttackWeakPunch()
{
	if (currAnimationFrame >= 3 && currAnimationFrame < 5)
	{
		isAttack = true;
		damage = 5;
	}
	else
	{
		isAttack = false;
		damage = 0;
	}

	if (currAnimationFrame >= maxWeakPunchFrame)
	{
		isWeakPunch = false;
		isAttack = false;
		damage = 0;
		currAnimationFrame = 0;
	}
}

void Character::AttackStrongPunch()
{
	if (currAnimationFrame >= 4 && currAnimationFrame <= 6)
	{
		isAttack = true;
		damage = 10;
	}
	else
	{
		isAttack = false;
		damage = 0;
	}

	if (currAnimationFrame >= maxStrongPunchFrame)
	{
		isStrongPunch = false;
		isAttack = false;
		damage = 0;
		currAnimationFrame = 0;
	}
}

void Character::AttackWeakKick()
{
	if (currAnimationFrame == 3)
	{
		isAttack = true;
		damage = 5;
	}
	else
	{
		isAttack = false;
		damage = 0;
	}

	if (currAnimationFrame >= maxWeakKickFrame)
	{
		isWeakKick = false;
		isAttack = false;
		damage = 0;
		currAnimationFrame = 0;
	}
}

void Character::AttackStrongKick()
{
	if (currAnimationFrame >= 6 && currAnimationFrame <= 9)
	{
		isAttack = true;
		damage = 10;
	}
	else
	{
		isAttack = false;
		damage = 0;
	}
	if (currAnimationFrame >= maxStrongKickFrame)
	{
		isStrongKick = false;
		isAttack = false;
		damage = 0;
		currAnimationFrame = 0;
	}
}


void Character::SetImage(const wchar_t* filePath , int width, int height, int maxAnimationFrame, int maxWalkFrame, int maxWeakPunchFrame,
	int maxStrongPunchFrame, int maxWeakKickFrame, int maxStrongKickFrame)
{

	if (FAILED(image->Init(filePath, width, height, maxAnimationFrame, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	
	this->maxAnimationFrame = maxAnimationFrame; 
	this->maxWalkFrame = maxWalkFrame;
	this->maxWeakPunchFrame = maxWeakPunchFrame;
	this->maxStrongPunchFrame = maxStrongPunchFrame;
	this->maxWeakKickFrame = maxWeakKickFrame;
	this->maxStrongKickFrame = maxStrongKickFrame;
}

Character::Character()
{
}

Character::~Character()
{
}
