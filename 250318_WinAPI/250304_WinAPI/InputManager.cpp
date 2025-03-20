#include "InputManager.h"

const PlayerKeyBind InputManager::player1 = { 'A', 'D', 'W', 'S', 'T', 'Y', 'G', 'H' };
const PlayerKeyBind InputManager::player2 = { VK_NUMPAD4, VK_NUMPAD6, VK_NUMPAD5, VK_NUMPAD8, '[', ']', ';', '\'' };

const PlayerKeyBind &InputManager::WhichPlayer(PLAYER player)
{
    if (PLAYER::Player1 == player)
        return InputManager::player1;
    return InputManager::player2;
}

bool InputManager::IsPlayerMoveLeft(PLAYER player)
{
    const PlayerKeyBind& character = WhichPlayer(player);

    if (KeyManager::GetInstance()->IsOnceKeyDown(character.Left)
        || KeyManager::GetInstance()->IsStayKeyDown(character.Left))
        return true;
    return false;
}

bool InputManager::IsPlayerMoveRight(PLAYER player)
{
    const PlayerKeyBind& character = WhichPlayer(player);

    if (KeyManager::GetInstance()->IsOnceKeyDown(character.Right)
        || KeyManager::GetInstance()->IsStayKeyDown(character.Right))
        return true;
    return false;
}

bool InputManager::IsPlayerMoveUp(PLAYER player)
{
    const PlayerKeyBind& character = WhichPlayer(player);

    if (KeyManager::GetInstance()->IsOnceKeyDown(character.Up)
        || KeyManager::GetInstance()->IsStayKeyDown(character.Up))
        return true;
    return false;
}

bool InputManager::IsPlayerMoveDown(PLAYER player)
{
    const PlayerKeyBind& character = WhichPlayer(player);

    if (KeyManager::GetInstance()->IsOnceKeyDown(character.Down)
        || KeyManager::GetInstance()->IsStayKeyDown(character.Down))
        return true;
    return false;
}

bool InputManager::IsPlayerAttackWeakPunch(PLAYER player)
{
    const PlayerKeyBind& character = WhichPlayer(player);

    if (KeyManager::GetInstance()->IsOnceKeyDown(character.WeakPunch))
        return true;
    return false;
}

bool InputManager::IsPlayerAttackWeakKick(PLAYER player)
{
    const PlayerKeyBind& character = WhichPlayer(player);

    if (KeyManager::GetInstance()->IsOnceKeyDown(character.WeakKick))
        return true;
    return false;
}

bool InputManager::IsPlayerAttackStrongPunch(PLAYER player)
{
    const PlayerKeyBind& character = WhichPlayer(player);

    if (KeyManager::GetInstance()->IsOnceKeyDown(character.StrongPunch))
        return true;
    return false;
}

bool InputManager::IsPlayerAttackStrongKick(PLAYER player)
{
    const PlayerKeyBind& character = WhichPlayer(player);

    if (KeyManager::GetInstance()->IsOnceKeyDown(character.StrongKick))
        return true;
    return false;
}

bool InputManager::IsPressAnyKey(void)
{
    return KeyManager::GetInstance()->IsPressAnyKey();
}
