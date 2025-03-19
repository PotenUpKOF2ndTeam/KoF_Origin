#include "InputManager.h"

const PlayerKeyBind InputManager::player1 = { 'A', 'D', 'W', 'S', 'T', 'Y', 'G', 'H' };
const PlayerKeyBind InputManager::player2 = { VK_NUMPAD4, VK_NUMPAD6, VK_NUMPAD5, VK_NUMPAD8, '[', ']', ';', '\'' };

bool InputManager::IsPlayer1MoveLeft(void)
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(InputManager::player1.Left)
        || KeyManager::GetInstance()->IsStayKeyDown(InputManager::player1.Left))
        return true;
    return false;
}

bool InputManager::IsPlayer1MoveRight(void)
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(InputManager::player1.Right)
        || KeyManager::GetInstance()->IsStayKeyDown(InputManager::player1.Right))
        return true;
    return false;
}

bool InputManager::IsPlayer1MoveUp(void)
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(InputManager::player1.Up)
        || KeyManager::GetInstance()->IsStayKeyDown(InputManager::player1.Up))
        return true;
    return false;
}

bool InputManager::IsPlayer1MoveDown(void)
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(InputManager::player1.Down)
        || KeyManager::GetInstance()->IsStayKeyDown(InputManager::player1.Down))
        return true;
    return false;
}

bool InputManager::IsPlayer1AttackWeakPunch(void)
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(InputManager::player1.WeakPunch))
        return true;
    return false;
}

bool InputManager::IsPlayer1AttackWeakKick(void)
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(InputManager::player1.WeakKick))
        return true;
    return false;
}

bool InputManager::IsPlayer1AttackStrongPunch(void)
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(InputManager::player1.StrongPunch))
        return true;
    return false;
}

bool InputManager::IsPlayer1AttackStrongKick(void)
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(InputManager::player1.StrongKick))
        return true;
    return false;
}
bool InputManager::IsPlayer2MoveLeft(void)
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(InputManager::player2.Left)
        || KeyManager::GetInstance()->IsStayKeyDown(InputManager::player2.Left))
        return true;
    return false;
}

bool InputManager::IsPlayer2MoveRight(void)
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(InputManager::player2.Right)
        || KeyManager::GetInstance()->IsStayKeyDown(InputManager::player2.Right))
        return true;
    return false;
}

bool InputManager::IsPlayer2MoveUp(void)
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(InputManager::player2.Up)
        || KeyManager::GetInstance()->IsStayKeyDown(InputManager::player2.Up))
        return true;
    return false;
}

bool InputManager::IsPlayer2MoveDown(void)
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(InputManager::player2.Down)
        || KeyManager::GetInstance()->IsStayKeyDown(InputManager::player2.Down))
        return true;
    return false;
}

bool InputManager::IsPlayer2AttackWeakPunch(void)
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(InputManager::player2.WeakPunch))
        return true;
    return false;
}

bool InputManager::IsPlayer2AttackWeakKick(void)
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(InputManager::player2.WeakKick))
        return true;
    return false;
}

bool InputManager::IsPlayer2AttackStrongPunch(void)
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(InputManager::player2.StrongPunch))
        return true;
    return false;
}

bool InputManager::IsPlayer2AttackStrongKick(void)
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(InputManager::player2.StrongKick))
        return true;
    return false;
}
