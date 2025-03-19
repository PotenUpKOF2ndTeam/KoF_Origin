#pragma once
#include "KeyManager.h"

typedef struct PlayerKeyBind
{
	int Left;
	int Right;
	int Up;
	int Down;
	int WeakPunch;
	int WeakKick;
	int StrongPunch;
	int StrongKick;
};

class InputManager
{
private:
	static const struct PlayerKeyBind player1;
	static const struct PlayerKeyBind player2;

public:
	static bool IsPlayer1MoveLeft(void);
	static bool IsPlayer1MoveRight(void);
	static bool IsPlayer1MoveUp(void);
	static bool IsPlayer1MoveDown(void);
	static bool IsPlayer1AttackWeakPunch(void);
	static bool IsPlayer1AttackWeakKick(void);
	static bool IsPlayer1AttackStrongPunch(void);
	static bool IsPlayer1AttackStrongKick(void);

	static bool IsPlayer2MoveLeft(void);
	static bool IsPlayer2MoveRight(void);
	static bool IsPlayer2MoveUp(void);
	static bool IsPlayer2MoveDown(void);
	static bool IsPlayer2AttackWeakPunch(void);
	static bool IsPlayer2AttackWeakKick(void);
	static bool IsPlayer2AttackStrongPunch(void);
	static bool IsPlayer2AttackStrongKick(void);
};


