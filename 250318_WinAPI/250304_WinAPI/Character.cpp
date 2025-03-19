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
	//�̹��� ����

	//����ġ 

	//����ġ

	//��ű
	
	//��ű
}

void Character::Move()
{
	// ������ �� �� 
	pos.x += moveSpeed;

	// �ڷ� �� �� 
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
