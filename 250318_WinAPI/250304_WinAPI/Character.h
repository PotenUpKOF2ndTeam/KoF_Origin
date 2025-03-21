#pragma once
#include "GameObject.h"
#include "InputManager.h"

#define PLAYER1_START_X 200
#define PLAYER_START_Y 150
#define PLAYER2_START_X 600

class Image;
class Character
{
public:


private:
	int weakDamage;
	int	strongDamage;
	int	HP;
	int damage;
	POINT pos;
	int	moveSpeed;
	int frame;
	int currAnimationFrame;
	
	int maxAnimationFrame;		
	int maxWalkFrame;
	int maxWeakPunchFrame;
	int maxStrongPunchFrame;
	int maxWeakKickFrame;
	int maxStrongKickFrame;
	
	bool isIdle;
	bool isMoveRight;
	bool isMoveLeft;
	bool isWeakPunch;
	bool isStrongPunch;
	bool isWeakKick;
	bool isStrongKick;
	bool isAttack;
	bool isDead;
	bool isFilp;

	PLAYER player;
	
	Image* image;

public:
	void Init(PLAYER playerType);
	void Release();
	void Update();
	void Render(HDC hdc);
	void Move();
	void OnDamaged(int damage);
	void Dead();
	void Attack();
	void AttackWeakPunch();
	void AttackStrongPunch();
	void AttackWeakKick();
	void AttackStrongKick();

	POINT GetPos() { return pos; }
	int GetWeakDamage() { return weakDamage; }
	int GetStrongDamage() { return strongDamage; }
	bool GetIsStrongPunch() { return isStrongPunch; }
	bool GetIsWeakPunch() { return isWeakPunch; }
	bool GetIsStrongKick() { return isStrongKick; }
	bool GetIsWeakKick() { return isWeakKick; }
	int GetHP() { return HP; }
	void SetImage(const wchar_t* filePath, int width, int height, int maxAnimationFrame, int maxWalkFrame, int maxWeakPunchFrame, 
					int maxStrongPunchFrame, int maxWeakKickFrame, int maxStrongKickFrame);	
	void SetUpdateHP();

	Character();
	~Character();

};

