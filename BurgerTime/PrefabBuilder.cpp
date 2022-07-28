#include "BurgerTimePCH.h"
#include "PrefabBuilder.h"

#include "Button.h"

dae::GameObject* Prefab::CreatePlayer(const Vector2& pos)
{
    dae::GameObject* pPlayer = new dae::GameObject{};
    pPlayer->SetPosition(pos);



    return pPlayer;
}

dae::GameObject* Prefab::CreateButton(const Vector2& pos, Command* pCommand)
{
    dae::GameObject* pButton = new dae::GameObject{};
    pButton->SetPosition(pos);

    pButton->AddComponent<Button>(new Button(pCommand));

    return pButton;
}
