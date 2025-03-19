#pragma once
#include "Character.h"

class CharacterIsLeft : public Character
{
private:
	Character RePlayer1;
	Character RePlayer2;
	
	POINT pos;


public:
	void Replication(Character& player1, Character& player2);

	void RenderBody(HDC hdc);


};

