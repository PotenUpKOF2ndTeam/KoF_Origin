#pragma once
#include "Character.h"



class HitDetection : public Character
{
private:

	Character* player1;
	Character* player2;

	POINT RePlayerPos1;
	POINT RePlayerPos2;

	RECT ChecekRenderBox1;
	RECT ChecekRenderBox2;

	POINT pos;


	// checkPosition이 true 일 시 1p 공격 false일 시 2p공격
	bool checkPosition;
	bool checkCollision;
	bool IsAttackP2;
	int count;

	// 공격 유형
	bool IsAttackP1WeakPunch;
	bool IsAttackP1StrongPunch;
	bool IsAttackP1WeakKick;
	bool IsAttackP1StrongKick;

	bool IsAttackP2WeakPunch;
	bool IsAttackP2StrongPunch;
	bool IsAttackP2WeakKick;
	bool IsAttackP2StrongKick;


public:

	void Init();

	void Release();

	void Replication(Character* player1, Character* player2);

	void Update();

	void OnDamage();



	void RePlayer1Render(HDC hdc);

	void RePlayer2Render(HDC hdc);

	void CheckPosition();

	void Attack(HDC hdc);

	void CheckCollision();

	bool LeftDefense();

	bool RightDefense();

	bool BottomLeftDefense();

	bool BottomRightDefense();



	HitDetection();
	~HitDetection();


};