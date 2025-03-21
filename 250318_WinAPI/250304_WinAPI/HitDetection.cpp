#include "HitDetection.h"
#include "CommonFunction.h"


// �÷��̾� �ʱ�ȭ
void HitDetection::Init()
{
	player1 = new Character;
	player2 = new Character;

	checkCollision1 = false;
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




	if (InputManager::IsPlayerAttackWeakPunch(player1->GetPlayer())) {
		IsAttackP1WeakPunch = !IsAttackP1WeakPunch;
	}
	if (InputManager::IsPlayerAttackStrongPunch(player1->GetPlayer())) {
		IsAttackP1StrongPunch = !IsAttackP1StrongPunch;
	}
	if (InputManager::IsPlayerAttackWeakKick(player1->GetPlayer())) {
		IsAttackP1WeakKick = !IsAttackP1WeakKick;
	}
	if (InputManager::IsPlayerAttackStrongKick(player1->GetPlayer())) {
		IsAttackP1StrongKick = !IsAttackP1StrongKick;
	}

	if (InputManager::IsPlayerAttackWeakPunch(player2->GetPlayer())) {
		IsAttackP2WeakPunch = !IsAttackP2WeakPunch;
	}
	if (InputManager::IsPlayerAttackStrongPunch(player2->GetPlayer())) {
		IsAttackP2StrongPunch = !IsAttackP2StrongPunch;
	}
	if (InputManager::IsPlayerAttackWeakKick(player2->GetPlayer())) {
		IsAttackP2WeakKick = !IsAttackP2WeakKick;
	}
	if (InputManager::IsPlayerAttackStrongKick(player2->GetPlayer())) {
		IsAttackP2StrongKick = !IsAttackP2StrongKick;
	}


	CheckPosition();
	CheckCollision();
	OnDamage();
}

void HitDetection::OnDamage()
{
	// 1p ����
	if (IsAttackP1WeakPunch && checkCollision1 && checkPosition) {
		if (RightDefense() || BottomRightDefense())
			return;
		else
			player2->OnDamaged(player1->GetDamage());
	}
	if (IsAttackP1StrongPunch && checkCollision1 && checkPosition) {
		if (RightDefense() || BottomRightDefense())
			return;
		else
			player2->OnDamaged(player1->GetDamage());
	}
	if (IsAttackP1WeakKick && checkCollision1 && checkPosition) {
		if (RightDefense() || BottomRightDefense())
			return;
		else
			player2->OnDamaged(player1->GetDamage());
	}
	if (IsAttackP1StrongKick && checkCollision1 && checkPosition) {
		if (RightDefense() || BottomRightDefense())
			return;
		else
			player2->OnDamaged(player1->GetDamage());
	}

	// 2p ����
	if (IsAttackP2WeakPunch && checkCollision2 && checkPosition) {
		if (RightDefense() || BottomRightDefense())
			return;
		else
			player1->OnDamaged(player2->GetDamage());
	}
	if (IsAttackP2StrongPunch && checkCollision2 && checkPosition) {
		if (RightDefense() || BottomRightDefense())
			return;
		else
			player1->OnDamaged(player2->GetDamage());
	}
	if (IsAttackP2WeakKick && checkCollision2 && checkPosition) {
		if (RightDefense() || BottomRightDefense())
			return;
		else
			player1->OnDamaged(player2->GetDamage());
	}
	if (IsAttackP2StrongKick && checkCollision2 && checkPosition) {
		if (RightDefense() || BottomRightDefense())
			return;
		else
			player1->OnDamaged(player2->GetDamage());
	}
}

// ��Ʈ ���� �ڽ� 1p
void HitDetection::RePlayer1Render(HDC hdc)
{
	RenderRectAtCenter(hdc, RePlayerPos1.x + 80, RePlayerPos1.y + 120, 50, 150);
	//(HDC hdc, int centerX, int centerY, int width, int height)

}

// ��Ʈ ���� �ڽ� 2p
void HitDetection::RePlayer2Render(HDC hdc)
{
	RenderRectAtCenter(hdc, RePlayerPos2.x + 120, RePlayerPos2.y + 120, 50, 150);
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
		RenderRectAtCenter(hdc, RePlayerPos1.x +150, RePlayerPos1.y + 100, 10, 10);
	}
	if (IsAttackP1StrongPunch) {
		RenderRectAtCenter(hdc, RePlayerPos1.x + 150, RePlayerPos1.y + 100, 10, 10);
		IsAttackP1StrongPunch = false;
	}
	if (IsAttackP1WeakKick) {
		RenderRectAtCenter(hdc, RePlayerPos1.x + 150, RePlayerPos1.y + 100, 10, 10);
		IsAttackP1WeakKick = false;
	}
	if (IsAttackP1StrongKick) {
		RenderRectAtCenter(hdc, RePlayerPos1.x + 160, RePlayerPos1.y + 120, 10, 10);
		IsAttackP1StrongKick = false;
	}


	if (IsAttackP2WeakPunch) {
		RenderRectAtCenter(hdc, RePlayerPos2.x + 20, RePlayerPos2.y + 100, 10, 10);
		IsAttackP2WeakPunch = false;
	}
	if (IsAttackP2StrongPunch) {
		RenderRectAtCenter(hdc, RePlayerPos2.x + 20, RePlayerPos2.y + 100, 10, 10);
		IsAttackP2StrongPunch = false;
	}
	if (IsAttackP2WeakKick) {
		RenderRectAtCenter(hdc, RePlayerPos2.x + 20, RePlayerPos2.y + 100, 10, 10);
		IsAttackP2WeakKick = false;
	}
	if (IsAttackP2StrongKick) {
		RenderRectAtCenter(hdc, RePlayerPos2.x + 20, RePlayerPos2.y + 120, 10, 10);
		IsAttackP2StrongKick = false;
	}
}


// CommonFuctuin.h �� �ִ� RectInfRect�� �浹 üũ
// true �� �� �浹
void HitDetection::CheckCollision()
{
	RECT intersection;
	// �� ���� �簢���� ��ġ�� ������ �κ��� �ִ��� üũ
	
	if (RePlayerPos1.x + 100 >= RePlayerPos2.x && RePlayerPos1.x <= RePlayerPos2.x + 100) {
		checkCollision1 = true;
	}
	else
		checkCollision1 = false;

	if (RePlayerPos2.x + 100 >= RePlayerPos1.x && RePlayerPos2.x <= RePlayerPos1.x + 100) {
		checkCollision2 = true;
	}
	else
		checkCollision2 = false;

	/*checkCollision1 = IntersectRect(&intersection, &CheckHitBox1, &ChecekRenderBox2);
	checkCollision2 = IntersectRect(&intersection, &CheckHitBox2, &ChecekRenderBox2);*/
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
