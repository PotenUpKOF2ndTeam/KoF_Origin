#include "HitDetection.h"
#include "CommonFunction.h"


// 플레이어 초기화
void HitDetection::Init()
{
	player1 = new Character;
	player2 = new Character;

	checkCollision1 = false;
	checkPosition = true;
	count = 0;


	// 1p 2p 공격 모션 false 초기화
	IsAttackP1WeakPunch = false;
	IsAttackP1StrongPunch = false;
	IsAttackP1WeakKick = false;
	IsAttackP1StrongKick = false;

	IsAttackP2WeakPunch = false;
	IsAttackP2StrongPunch = false;
	IsAttackP2WeakKick = false;
	IsAttackP2StrongKick = false;

}

// 메모리 초기화
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

// player 복제
void HitDetection::Replication(Character* player1, Character* player2)
{
	// pos x와 y를 복제해야 함
	this->player1 = player1;
	this->player2 = player2;

}

// 업데이트
void HitDetection::Update()
{
	// 복제된 플레이어 업데이트
	player1->Update();
	player2->Update();

	// 복제 플레이어 좌표 설정
	RePlayerPos1 = player1->GetPos();
	RePlayerPos2 = player2->GetPos();

	int centerX = RePlayerPos1.x + 25;
	int centerY = RePlayerPos1.x + 50;
	int width = 50;
	int height = 100;
	// width, height 지워야 할 변수

	int centerX2 = RePlayerPos2.x + 225;
	int centerY2 = RePlayerPos2.x + 50;
	int width2 = 50;
	int height2 = 100;
	// width, height 지워야 할 변수


	ChecekRenderBox1.right = RePlayerPos1.x + 50;
	ChecekRenderBox1.left = RePlayerPos1.x;
	// 확장성을 위해 top, bottom 필요하긴 함

	ChecekRenderBox2.right = RePlayerPos2.x + 250;
	ChecekRenderBox2.left = RePlayerPos2.x + 200;
	// 플레이어 2개 따로 그려지면 pos가 맞는지 확인해야함




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
	// 1p 공격
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

	// 2p 공격
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

// 히트 판정 박스 1p
void HitDetection::RePlayer1Render(HDC hdc)
{
	RenderRectAtCenter(hdc, RePlayerPos1.x + 80, RePlayerPos1.y + 120, 50, 150);
	//(HDC hdc, int centerX, int centerY, int width, int height)

}

// 히트 판정 박스 2p
void HitDetection::RePlayer2Render(HDC hdc)
{
	RenderRectAtCenter(hdc, RePlayerPos2.x + 120, RePlayerPos2.y + 120, 50, 150);
}

// 1p 2p 위치 비교
void HitDetection::CheckPosition()
{
	if (ChecekRenderBox1.right < ChecekRenderBox2.left) {
		checkPosition = true;
	}
	else
		checkPosition = false;
}

// 복제 플레이어 공격 위치 그리기
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


// CommonFuctuin.h 에 있는 RectInfRect로 충돌 체크
// true 일 시 충돌
void HitDetection::CheckCollision()
{
	RECT intersection;
	// 두 개의 사각형이 겹치는 교집합 부분이 있는지 체크
	
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




// 방어 처리
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

//플레이어가 왼쪽을 누른상태로 아래쪽 버튼도 누르면 참
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
