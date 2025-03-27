#pragma once
#include "GameObject.h"
#include "InputManager.h"

#define PLAYER1_START_X 200
#define PLAYER_START_Y 240
#define PLAYER2_START_X 600

class Image;
class Character
{
public:


private:	
	int	HP;
	int damage;
	POINT pos;
	int	moveSpeed;
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
	void AttackWeakPunch();
	void AttackStrongPunch();
	void AttackWeakKick();
	void AttackStrongKick();

	POINT GetPos() { return pos; }	
	int GetHP() { return HP; }
	bool GetIsAttack() { return isAttack; }
	int GetDamage() { return damage; }
	PLAYER GetPlayer() const { return player; }

	void SetImage(const wchar_t* filePath, int width, int height, int maxAnimationFrame, int maxWalkFrame, int maxWeakPunchFrame, 
					int maxStrongPunchFrame, int maxWeakKickFrame, int maxStrongKickFrame);		
	

	Character();
	~Character();

};

