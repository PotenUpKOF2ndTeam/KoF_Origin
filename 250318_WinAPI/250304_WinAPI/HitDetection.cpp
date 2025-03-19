#include "HitDetection.h"
#include "Character.h"

void HitDetection::Init()
{
	player1 = new Character;
	player2 = new Character;
}

void HitDetection::Update()
{
	OnDamage(player1, player2);
}

void HitDetection::Release()
{
	if (player1) {
		player1->Release();
		delete player1;
		player1 = nullptr;
	}

	if (player2) {
		player2->Release();
		delete player2;
		player2 = nullptr;
	}
}


// ������ true, �浹 true �� �� �÷��̾��� ü�� ����
void HitDetection::OnDamage(Character* player1, Character* player2)
{
	this->player2 = player2;
	this->player1 = player1;
	if ((player1->GetIsWeakPunch() || player1->GetIsWeakKick()) && CheckCollision(player1, player2)) {
		//player2->OnDamaged(/*������ �ֱ�*/);
	}
	else if ((player1->GetIsStrongPunch() || player1->GetIsStrongPunch()) && CheckCollision(player1, player2)) {
		//player2->OnDamaged(/*������ �ֱ�*/);
	}
	else if ((player2->GetIsWeakPunch() || player2->GetIsWeakKick()) && CheckCollision(player2, player2)) {
		//player1->OnDamaged(/*������ �ֱ�*/);
	}
	else if ((player2->GetIsStrongPunch() || player2->GetIsStrongPunch()) && CheckCollision(player2, player2)) {
		//player1->OnDamaged(/*������ �ֱ�*/);
	}

}

// �÷��̾� ���� �浹 ó��
bool HitDetection::CheckCollision(Character* player1, Character* player2)
{
	this->player1 = player1;
	this->player2 = player2;
	
	//if(�÷��̾� �浹)
	//	return ture;
	//else
	//	return false;
	

	return false;
}


// ��� ó��
bool HitDetection::leftDefense()
{
	if (InputManager::IsPlayer1MoveLeft || InputManager::IsPlayer2MoveLeft)
		return true;
	return false;
}

bool HitDetection::RightDefense()
{
	if (InputManager::IsPlayer1MoveRight || InputManager::IsPlayer2MoveRight)
		return true;
	return false;
}

//�÷��̾ ������ �������·� �Ʒ��� ��ư�� ������ ��
bool HitDetection::BottomLeftDefense()
{
	if ((InputManager::IsPlayer1MoveLeft && InputManager::IsPlayer1MoveDown) || (InputManager::IsPlayer2MoveLeft && InputManager::IsPlayer2MoveDown))
		return true;
	return false;
}

bool HitDetection::BottomRightDefense()
{
	if ((InputManager::IsPlayer1MoveRight && InputManager::IsPlayer1MoveDown) || (InputManager::IsPlayer2MoveRight && InputManager::IsPlayer2MoveDown))
		return true;
	return false;
}


HitDetection::HitDetection()
{
}

HitDetection::~HitDetection()
{
}
