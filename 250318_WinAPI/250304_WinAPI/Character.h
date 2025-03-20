#pragma once
#include "GameObject.h"
#include "InputManager.h"

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
	int elapsedFrame;
	
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
	bool isDefend;
	bool isDead;

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

	void Punch();
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
	
	int SetMaxAnimationFrame(int maxAnimationFrame) { this->maxAnimationFrame = maxAnimationFrame; }

	void SetUpdateHP();

	Character();
	~Character();

};

