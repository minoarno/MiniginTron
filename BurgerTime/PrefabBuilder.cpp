#include "TronPCH.h"
#include "PrefabBuilder.h"

#include "Button.h"
#include "TextureComponent.h"
#include "RigidBody.h"
#include "BoxCollider.h"

#include "InputManager.h"
#include "TronCommands.h"
#include "JsonLevelLoader.h"
#include "EnemyLogic.h"
#include "BulletComponent.h"

#include "Player.h"
#include "Lives.h"
#include "LivesDisplay.h"
#include "Score.h"
#include "ScoreDisplay.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "Diamond.h"
#include "HighScore.h"

dae::GameObject* Prefab::CreatePlayer(const Vector2& pos, InputDesc inputDesc, dae::Scene* pScene)
{
    Vector2 dims{ 24,24 };
    dae::GameObject* pPlayer = new dae::GameObject{};
    pPlayer->SetPosition(pos);
    pPlayer->SetScene(pScene);

    pPlayer->SetTexture("RedTank.png");
    pPlayer->GetComponent<TextureComponent>()->SetDestinationRectDimensions(dims);

    pPlayer->AddComponent(new RigidBody(false));
    pPlayer->AddComponent(new BoxCollider(dims, {dims.x /2, dims.y / 2 }));
    pPlayer->AddComponent(new Player{ 3 });

    InputManager::GetInstance().AddOnRelease(inputDesc.moveUp,      new MoveCommand(pPlayer, 500, { 0,-1 }), inputDesc.playerIndex);
    InputManager::GetInstance().AddOnRelease(inputDesc.moveDown,    new MoveCommand(pPlayer, 500, { 0, 1 }), inputDesc.playerIndex);
    InputManager::GetInstance().AddOnRelease(inputDesc.moveLeft,    new MoveCommand(pPlayer, 500, { -1, 0 }), inputDesc.playerIndex);
    InputManager::GetInstance().AddOnRelease(inputDesc.moveRight,   new MoveCommand(pPlayer, 500, { 1, 0 }), inputDesc.playerIndex);
    InputManager::GetInstance().AddOnRelease(inputDesc.rotateLeft,  new RotateCommand(pPlayer, true), inputDesc.playerIndex);
    InputManager::GetInstance().AddOnRelease(inputDesc.rotateRight, new RotateCommand(pPlayer, false), inputDesc.playerIndex);
    InputManager::GetInstance().AddOnRelease(inputDesc.shoot,       new ShootCommand(pPlayer, 100, "PlayerBullet"), inputDesc.playerIndex);

    pPlayer->SetTag("Player");
    return pPlayer;
}

dae::GameObject* Prefab::CreateButton(const Rect& boundaries, Command* pCommand, const std::string& filepath)
{
    dae::GameObject* pButton = new dae::GameObject{};
    pButton->SetPosition({ boundaries .x,boundaries.y});

    pButton->SetTexture(filepath);
    pButton->GetComponent<TextureComponent>()->SetDestinationRectDimensions({ boundaries.w,boundaries.h });

    pButton->AddComponent<Button>(new Button({boundaries.w,boundaries.h}, pCommand));

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
    pBlock->AddComponent(new BoxCollider({ dims.x, dims.y }, {dims.x / 2, dims.y / 2}));
    pBlock->SetTag("Level");
    return pBlock;
}

dae::GameObject* Prefab::CreateLevel(const std::string& filepath, dae::Scene* pScene)
{
    dae::GameObject* pLevel = new dae::GameObject{};
    pLevel->SetPosition({0,0});
    pLevel->SetScene(pScene);

    JsonLevelLoader::LoadSceneUsingJson(pLevel, filepath);

    return pLevel;
}

dae::GameObject* Prefab::CreateBlueTank(const Vector2& pos, dae::Scene* pScene, const std::vector<Player*>& pPlayers)
{
    Vector2 dims{ 22,22 };

    dae::GameObject* pTank = new dae::GameObject{};
    pTank->SetScene(pScene);
    pTank->SetPosition(pos);

    pTank->SetTexture("BlueTank.png");
    pTank->GetComponent<TextureComponent>()->SetDestinationRectDimensions(dims);

    pTank->AddComponent(new RigidBody(false));
    pTank->AddComponent(new BoxCollider(dims, { dims.x / 2, dims.y / 2 }));

    pTank->AddComponent(new EnemyLogic{ 100,100,3,pPlayers });
    pTank->SetTag("Enemy");
    return pTank;
}

dae::GameObject* Prefab::CreateRecognizer(const Vector2& pos, dae::Scene* pScene, const std::vector<Player*>& pPlayers)
{
    Vector2 dims{ 22,22 };

    dae::GameObject* pRecognizer = new dae::GameObject{};
    pRecognizer->SetScene(pScene);
    pRecognizer->SetPosition(pos);

    pRecognizer->SetTexture("Recognizer.png");
    pRecognizer->GetComponent<TextureComponent>()->SetDestinationRectDimensions(dims);

    pRecognizer->AddComponent(new RigidBody(false));
    pRecognizer->AddComponent(new BoxCollider(dims, { dims.x / 2, dims.y / 2 }));

    pRecognizer->AddComponent(new EnemyLogic{ 200,250,3, pPlayers});
    pRecognizer->SetTag("Enemy");
    return pRecognizer;
}

dae::GameObject* Prefab::CreateBullet(const Vector2& pos, const Vector2& direction, dae::Scene* pScene, const std::string& tagBullet, Player* pPlayer)
{
    Vector2 dims{ 4,4 };

    dae::GameObject* pBullet = new dae::GameObject{};
    pBullet->SetScene(pScene);
    pBullet->SetPosition(pos);

    pBullet->SetTexture("Bullet.png");
    pBullet->GetComponent<TextureComponent>()->SetDestinationRectDimensions(dims);

    RigidBody* pRigid = pBullet->AddComponent(new RigidBody(false));
    pRigid->Move(direction.x * 200, direction.y * 200);
    pBullet->AddComponent(new BoxCollider(dims, { dims.x / 2, dims.y / 2 }));

    pBullet->AddComponent(new BulletComponent{ pPlayer });
    pBullet->SetTag(tagBullet);
    return pBullet;
}

dae::GameObject* Prefab::CreateLiveText(const Vector2& pos, Lives* pLives)
{
    dae::GameObject* pObject = new dae::GameObject{};
    pObject->AddComponent(new TextComponent{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) });
    pObject->AddComponent(new LivesDisplay{ pLives });
    pObject->SetPosition(pos);
    return pObject;
}

dae::GameObject* Prefab::CreateScoreText(const Vector2& pos, Score* pScore)
{
    dae::GameObject* pObject = new dae::GameObject{};
    pObject->AddComponent(new TextComponent{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) });
    pObject->AddComponent(new ScoreDisplay{ pScore });
    pObject->SetPosition(pos);
    return pObject;
}

dae::GameObject* Prefab::CreateDiamond(const Vector2& pos, const std::function<void()>& func, dae::Scene* pScene)
{
    Vector2 dims{ 48,48 };

    dae::GameObject* pDiamond = new dae::GameObject{};
    pDiamond->SetScene(pScene);
    pDiamond->SetPosition(pos);

    pDiamond->SetTexture("Diamond.png");
    pDiamond->GetComponent<TextureComponent>()->SetDestinationRectDimensions(dims);

    pDiamond->AddComponent(new RigidBody(true));
    pDiamond->AddComponent(new BoxCollider(dims, { dims.x / 2, dims.y / 2 }));

    pDiamond->AddComponent(new Diamond{ func });
    pDiamond->SetTag("Level");
    return pDiamond;
}

dae::GameObject* Prefab::CreateHighScoreList(const Vector2& pos, const std::string& filepath, HighScore* pHighScore)
{
    dae::GameObject* pHighScores = new dae::GameObject{};
    pHighScores->SetPosition(pos);

    JsonLevelLoader::LoadHighScore(filepath, pHighScore);
    //pHighScore->

    return pHighScores;
}
