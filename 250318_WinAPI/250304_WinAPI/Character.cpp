#include "Character.h"
#include "Image.h"

void Character::Init()
{
	weakDamage = 10;
	strongDamage = 15;
	HP = 100;
	pos = { 0,0 };
	moveSpeed = 5;
	currAnimationFrame = 0; 
	elapsedFrame = 0;

	isWeakPunch = false;
	isStrongPunch = false;
	isWeakKick = false;
	isStrongKick = false;
	isDefend = false;
	isDead = false;

	image = new Image;
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
	Move();

}

void Character::Render()
{
	//이미지 랜더

	//강펀치 

	//약펀치

	//강킥
	
	//약킥
}

void Character::Move()
{
	// 앞으로 갈 떄 
	pos.x += moveSpeed;

	// 뒤로 갈 때 
	pos.x -= moveSpeed;
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
