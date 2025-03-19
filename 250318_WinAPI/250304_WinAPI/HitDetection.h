#pragma once
#include "InputManager.h"

class Character;
class HitDetection
{
private:
	Character* player1;
	Character* player2;

public:	
	
	void Init();

	void Update();

	void Release();

	void OnDamage(Character* player1, Character* player2);

	bool CheckCollision(Character* player1, Character* player2);

	bool leftDefense();

	bool RightDefense();

	bool BottomLeftDefense();

	bool BottomRightDefense();


	HitDetection();
	~HitDetection();


};

