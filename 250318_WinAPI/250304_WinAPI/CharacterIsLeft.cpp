#include "CharacterIsLeft.h"

void CharacterIsLeft::Replication(Character& player1, Character& player2)
{
	// pos x�� y�� �����ؾ� ��(�����ʿ�)
	this->RePlayer1 = player1;
	this->RePlayer2 = player2;

}

void CharacterIsLeft::RenderBody(HDC hdc)
{
	// ���⼭ �簢���� �׷��ش�.

}


