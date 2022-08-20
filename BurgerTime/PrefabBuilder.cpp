#include "TronPCH.h"
#include "PrefabBuilder.h"

#include "Button.h"
#include "TextureComponent.h"
#include "RigidBody.h"
#include "BoxCollider.h"

#include "InputManager.h"

#include "TronCommands.h"

#include "JsonLevelLoader.h"

dae::GameObject* Prefab::CreatePlayer(const Vector2& pos, DWORD playerIndex, dae::Scene* pScene)
{
    dae::GameObject* pPlayer = new dae::GameObject{};
    pPlayer->SetPosition(pos);
    pPlayer->SetScene(pScene);

    pPlayer->SetTexture("RedTank.png");
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

dae::GameObject* Prefab::CreateBlock(const Vector2& pos, const Vector2& dims, dae::Scene* pScene)
{
    dae::GameObject* pBlock = new dae::GameObject{};
    pBlock->SetPosition(pos);
    pBlock->SetScene(pScene);

    pBlock->SetTexture("LevelBlock.png");
    pBlock->GetComponent<TextureComponent>()->SetDestinationRectDimensions({ dims.x, dims.y });

    return pBlock;
}

dae::GameObject* Prefab::CreateLevel(const std::string& filepath, dae::Scene* pScene)
{
    dae::GameObject* pLevel = new dae::GameObject{};
    pLevel->SetPosition({0,200});
    pLevel->SetScene(pScene);

    JsonLevelLoader::LoadSceneUsingJson(pLevel, filepath, nullptr);

    return pLevel;
}