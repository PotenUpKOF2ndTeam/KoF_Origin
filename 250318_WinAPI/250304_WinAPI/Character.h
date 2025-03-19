#pragma once
#include "GameObject.h"

class Image;
class Character
{
private:
	int weakDamage;
	int	strongDamage;
	int	HP;
	POINT pos;
	int	moveSpeed;
	int currAnimationFrame;
	int elapsedFrame;

	bool isWeakPunch;
	bool isStrongPunch;
	bool isWeakKick;
	bool isStrongKick;
	bool isDefend;
	bool isDead;

	Image* image;

public : 
	void Init();
	void Release();
	void Update();
	void Render();
	void Move();
	void OnDamaged(int damage);
	void Dead();
	bool GetIsStrongPunch() { return isStrongPunch;}
	bool GetIsWeakPunch() { return isWeakPunch; }
	bool GetIsStrongKick() { return isStrongKick; }
	bool GetIsWeakKick() { return isWeakKick; }
	int GetHP() { return HP; }
	void SetUpdateHP();

	Character();
	~Character();

};

