#include "HitDetection.h"
#include "CommonFunction.h"


// �÷��̾� �ʱ�ȭ
void HitDetection::Init()
{
	player1 = new Character;
	player2 = new Character;

	checkCollision = false;
	checkPosition = true;
	count = 0;


	// 1p 2p ���� ��� false �ʱ�ȭ
	IsAttackP1WeakPunch = false;
	IsAttackP1StrongPunch = false;
	IsAttackP1WeakKick = false;
	IsAttackP1StrongKick = false;

	IsAttackP2WeakPunch = false;
	IsAttackP2StrongPunch = false;
	IsAttackP2WeakKick = false;
	IsAttackP2StrongKick = false;

}

// �޸� �ʱ�ȭ
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

// player ����
void HitDetection::Replication(Character* player1, Character* player2)
{
	// pos x�� y�� �����ؾ� ��
	this->player1 = player1;
	this->player2 = player2;

}

// ������Ʈ
void HitDetection::Update()
{
	// ������ �÷��̾� ������Ʈ
	player1->Update();
	player2->Update();

	// ���� �÷��̾� ��ǥ ����
	RePlayerPos1 = player1->GetPos();
	RePlayerPos2 = player2->GetPos();

	int centerX = RePlayerPos1.x + 25;
	int centerY = RePlayerPos1.x + 50;
	int width = 50;
	int height = 100;
	// width, height ������ �� ����

	int centerX2 = RePlayerPos2.x + 225;
	int centerY2 = RePlayerPos2.x + 50;
	int width2 = 50;
	int height2 = 100;
	// width, height ������ �� ����


	ChecekRenderBox1.right = RePlayerPos1.x + 50;
	ChecekRenderBox1.left = RePlayerPos1.x;
	// Ȯ�强�� ���� top, bottom �ʿ��ϱ� ��

	ChecekRenderBox2.right = RePlayerPos2.x + 250;
	ChecekRenderBox2.left = RePlayerPos2.x + 200;
	// �÷��̾� 2�� ���� �׷����� pos�� �´��� Ȯ���ؾ���




	/*if (InputManager::IsPlayer1AttackWeakPunch()) {
		IsAttackP1WeakPunch = !IsAttackP1WeakPunch;
	}
	if (InputManager::IsPlayer1AttackStrongPunch()) {
		IsAttackP1StrongPunch = !IsAttackP1StrongPunch;
	}
	if (InputManager::IsPlayer1AttackWeakKick()) {
		IsAttackP1WeakKick = !IsAttackP1WeakKick;
	}
	if (InputManager::IsPlayer1AttackStrongKick()) {
		IsAttackP1StrongKick = !IsAttackP1StrongKick;
	}*/
	CheckPosition();
	CheckCollision();
	OnDamage();
}

void HitDetection::OnDamage()
{
	// 1p ����
	if (IsAttackP1WeakPunch && checkCollision && checkPosition) {
		if (RightDefense() || BottomRightDefense())
			return;
		else
			player2->OnDamaged(player1->GetDamage());
	}
	if (IsAttackP1StrongPunch && checkCollision && checkPosition) {
		if (RightDefense() || BottomRightDefense())
			return;
		else
			player2->OnDamaged(player1->GetDamage());
	}
	if (IsAttackP1WeakKick && checkCollision && checkPosition) {
		if (RightDefense() || BottomRightDefense())
			return;
		else
			player2->OnDamaged(player1->GetDamage());
	}
	if (IsAttackP1StrongKick && checkCollision && checkPosition) {
		if (RightDefense() || BottomRightDefense())
			return;
		else
			player2->OnDamaged(player1->GetDamage());
	}

	// 2p ����
	if (IsAttackP2WeakPunch && checkCollision && checkPosition) {
		if (RightDefense() || BottomRightDefense())
			return;
		else
			player1->OnDamaged(player2->GetDamage());
	}
	if (IsAttackP2StrongPunch && checkCollision && checkPosition) {
		if (RightDefense() || BottomRightDefense())
			return;
		else
			player1->OnDamaged(player2->GetDamage());
	}
	if (IsAttackP2WeakKick && checkCollision && checkPosition) {
		if (RightDefense() || BottomRightDefense())
			return;
		else
			player1->OnDamaged(player2->GetDamage());
	}
	if (IsAttackP2StrongKick && checkCollision && checkPosition) {
		if (RightDefense() || BottomRightDefense())
			return;
		else
			player1->OnDamaged(player2->GetDamage());
	}
}

// ��Ʈ ���� �ڽ� 1p
void HitDetection::RePlayer1Render(HDC hdc)
{
	RenderRectAtCenter(hdc, RePlayerPos1.x + 25, RePlayerPos1.y + 50, 50, 100);
	//(HDC hdc, int centerX, int centerY, int width, int height)

}

// ��Ʈ ���� �ڽ� 2p
void HitDetection::RePlayer2Render(HDC hdc)
{
	RenderRectAtCenter(hdc, 225, 50, 50, 100);
}

// 1p 2p ��ġ ��
void HitDetection::CheckPosition()
{
	if (ChecekRenderBox1.right < ChecekRenderBox2.left) {
		checkPosition = true;
	}
	else
		checkPosition = false;
}

// ���� �÷��̾� ���� ��ġ �׸���
void HitDetection::Attack(HDC hdc)
{
	if (IsAttackP1WeakPunch) {
		RenderRectAtCenter(hdc, RePlayerPos1.x + 70, RePlayerPos1.y + 20, 10, 10);
		IsAttackP1WeakPunch = false;
	}
	if (IsAttackP1StrongPunch) {
		RenderRectAtCenter(hdc, RePlayerPos1.x + 70, RePlayerPos1.y + 20, 10, 10);
		IsAttackP1StrongPunch = false;
	}
	if (IsAttackP1WeakKick) {
		RenderRectAtCenter(hdc, RePlayerPos1.x + 70, RePlayerPos1.y + 50, 10, 10);
		IsAttackP1WeakKick = false;
	}
	if (IsAttackP1StrongKick) {
		RenderRectAtCenter(hdc, RePlayerPos1.x + 70, RePlayerPos1.y + 50, 10, 10);
		IsAttackP1StrongKick = false;
	}


	// �÷��̾� 2 ��Ʈ ���� ��ġ ���� �ؾ��մϴ�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (IsAttackP2WeakPunch) {
		RenderRectAtCenter(hdc, RePlayerPos2.x + 70, RePlayerPos2.y + 20, 10, 10);
	}
	if (IsAttackP2StrongPunch) {
		RenderRectAtCenter(hdc, RePlayerPos2.x + 70, RePlayerPos2.y + 20, 10, 10);
	}
	if (IsAttackP2WeakKick) {
		RenderRectAtCenter(hdc, RePlayerPos2.x + 70, RePlayerPos2.y, 10, 10);
	}
	if (IsAttackP2StrongKick) {
		RenderRectAtCenter(hdc, RePlayerPos2.x + 70, RePlayerPos2.y, 10, 10);
	}
}


// CommonFuctuin.h �� �ִ� RectInfRect�� �浹 üũ
// true �� �� �浹
void HitDetection::CheckCollision()
{
	RECT intersection;
	// �� ���� �簢���� ��ġ�� ������ �κ��� �ִ��� üũ
	checkCollision = IntersectRect(&intersection, &ChecekRenderBox1, &ChecekRenderBox2);
}




// ��� ó��
bool HitDetection::LeftDefense()
{
	//if (InputManager::IsPlayer1MoveLeft/* || InputManager::IsPlayer2MoveLeft*/)
	//	return true;
	return false;
}

bool HitDetection::RightDefense()
{
	//if (/*InputManager::IsPlayer1MoveRight ||*/ InputManager::IsPlayer2MoveRight)
	//	return true;
	return false;
}

//�÷��̾ ������ �������·� �Ʒ��� ��ư�� ������ ��
bool HitDetection::BottomLeftDefense()
{
	//if ((InputManager::IsPlayer1MoveLeft && InputManager::IsPlayer1MoveDown)/* || (InputManager::IsPlayer2MoveLeft && InputManager::IsPlayer2MoveDown)*/)
	//	return true;
	return false;
}

bool HitDetection::BottomRightDefense()
{
	//if ((InputManager::IsPlayer1MoveRight && InputManager::IsPlayer1MoveDown)/* || (InputManager::IsPlayer2MoveRight && InputManager::IsPlayer2MoveDown)*/)
	//	return true;
	return false;
}





HitDetection::HitDetection()
{
}

HitDetection::~HitDetection()
{
}
