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

    pPlayer->AddComponent(new RigidBody(false));
    pPlayer->AddComponent(new BoxCollider({ 40,40 }, { 20, 20 }));

    InputManager::GetInstance().AddOnRelease(ControllerButton::DPadUp,      new MoveCommand(pPlayer, 500, { 0,-1 }), playerIndex);
    InputManager::GetInstance().AddOnRelease(ControllerButton::DPadDown,    new MoveCommand(pPlayer, 500, { 0, 1 }), playerIndex);
    InputManager::GetInstance().AddOnRelease(ControllerButton::DPadLeft,    new MoveCommand(pPlayer, 500, { -1, 0 }), playerIndex);
    InputManager::GetInstance().AddOnRelease(ControllerButton::DPadRight,   new MoveCommand(pPlayer, 500, { 1, 0 }), playerIndex);

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

    pBlock->AddComponent(new RigidBody(true));
    pBlock->AddComponent(new BoxCollider({ dims.x, dims.y }, {pos.x + dims.x / 2, pos.y + dims.y / 2 }));

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

dae::GameObject* Prefab::CreateTank(const Vector2& pos, dae::Scene* pScene)
{
    dae::GameObject* pTank = new dae::GameObject{};
    pTank->SetScene(pScene);
    pTank->SetPosition(pos);

    pTank->SetTexture("BlueTank.png");
    pTank->GetComponent<TextureComponent>()->SetDestinationRectDimensions({ 32 , 32 });

    pTank->AddComponent(new RigidBody(false));
    pTank->AddComponent(new BoxCollider({ 32,32 }, { 16, 16 }));

    return pTank;
}
