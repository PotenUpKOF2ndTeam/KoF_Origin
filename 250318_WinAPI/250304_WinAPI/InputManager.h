#pragma once
#include "KeyManager.h"
#include "Character.h"

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
	static const PlayerKeyBind& WhichPlayer(PLAYER player);

public:
	virtual ~InputManager() = 0;
	static bool IsPlayerMoveLeft(PLAYER player);
	static bool IsPlayerMoveRight(PLAYER player);
	static bool IsPlayerMoveUp(PLAYER player);
	static bool IsPlayerMoveDown(PLAYER player);
	static bool IsPlayerAttackWeakPunch(PLAYER player);
	static bool IsPlayerAttackWeakKick(PLAYER player);
	static bool IsPlayerAttackStrongPunch(PLAYER player);
	static bool IsPlayerAttackStrongKick(PLAYER player);
	static bool IsPressAnyKey(void);
};


