#pragma once
#include "GameObject.h"
#include "InputManager.h"

class Image;
class Character
{
public:
	enum class PLAYER : uint8_t
	{
		Player1,
		Player2,
		END
	};

private:
	int weakDamage;
	int	strongDamage;
	int	HP;
	POINT pos;
	int	moveSpeed;
	float frame;
	float currAnimationFrame;
	float elapsedFrame;

	bool isMoveRight;
	bool isMoveLeft;
	bool isWeakPunch;
	bool isStrongPunch;
	bool isWeakKick;
	bool isStrongKick;
	bool isDefend;
	bool isDead;

	PLAYER player;

	Image* image;


public:
	void Init(PLAYER playerType);
	void Release();
	void Update(int frame);
	void Render(HDC hdc);
	void Move();
	void OnDamaged(int damage);
	void Dead();
	POINT GetPos() { return pos; }
	int GetWeakDamage() { return weakDamage; }
	int GetStrongDamage() { return strongDamage; }
	bool GetIsStrongPunch() { return isStrongPunch; }
	bool GetIsWeakPunch() { return isWeakPunch; }
	bool GetIsStrongKick() { return isStrongKick; }
	bool GetIsWeakKick() { return isWeakKick; }
	int GetHP() { return HP; }

	void SetUpdateHP();



	Character();
	~Character();

};

