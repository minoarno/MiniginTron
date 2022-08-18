#include "TronPCH.h"
#include "PrefabBuilder.h"

#include "Button.h"
#include "TextureComponent.h"

#include "InputManager.h"

#include "TronCommands.h"

dae::GameObject* Prefab::CreatePlayer(const Vector2& pos, DWORD playerIndex)
{
    dae::GameObject* pPlayer = new dae::GameObject{};
    pPlayer->SetPosition(pos);

    pPlayer->SetTexture("PeterPepper.png",9,2);
    pPlayer->GetComponent<TextureComponent>()->SetDestinationRectDimensions({ 40,40 });

    InputManager::GetInstance().AddOnRelease(ControllerButton::DPadUp,      new MoveCommand(pPlayer, 50, { 0,-1 }), playerIndex);
    InputManager::GetInstance().AddOnRelease(ControllerButton::DPadDown,    new MoveCommand(pPlayer, 50, { 0, 1 }), playerIndex);
    InputManager::GetInstance().AddOnRelease(ControllerButton::DPadLeft,    new MoveCommand(pPlayer, 50, { -1, 0 }), playerIndex);
    InputManager::GetInstance().AddOnRelease(ControllerButton::DPadRight,   new MoveCommand(pPlayer, 50, { 1, 0 }), playerIndex);

    return pPlayer;
}

dae::GameObject* Prefab::CreateButton(const Vector2& pos, Command* pCommand)
{
    dae::GameObject* pButton = new dae::GameObject{};
    pButton->SetPosition(pos);

    pButton->AddComponent<Button>(new Button(pCommand));

    return pButton;
}