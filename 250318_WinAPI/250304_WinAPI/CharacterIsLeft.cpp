#include "CharacterIsLeft.h"

void CharacterIsLeft::Replication(Character& player1, Character& player2)
{
	// pos x와 y를 복제해야 함(수정필요)
	this->RePlayer1 = player1;
	this->RePlayer2 = player2;

}

void CharacterIsLeft::RenderBody(HDC hdc)
{
	// 여기서 사각형을 그려준다.

}


