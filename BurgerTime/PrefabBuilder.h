#pragma once
#include "GameObject.h"
#include "HelperStructs.h"

namespace dae
{
	class Scene;
}
class Command;
struct InputDesc;
class Lives;
class Score;
class Player;
class HighScore;
namespace Prefab
{
	dae::GameObject* CreatePlayer(const Vector2& pos, InputDesc inputDesc, dae::Scene* pScene);
	dae::GameObject* CreateButton(const Rect& pos, Command* pCommand, const std::string& filepath);
	dae::GameObject* CreateBlock(const Vector2& pos, const Vector2& dims, dae::Scene* pScene);
	dae::GameObject* CreateLevel(const std::string& filepath, dae::Scene* pScene);
	dae::GameObject* CreateBlueTank(const Vector2& pos, dae::Scene* pScene, const std::vector<Player*>& pPlayers);
	dae::GameObject* CreateRecognizer(const Vector2& pos, dae::Scene* pScene, const std::vector<Player*>& pPlayers);
	dae::GameObject* CreateBullet(const Vector2& pos, const Vector2& direction , dae::Scene* pScene, const std::string& tagBullet, Player* pPlayer = nullptr);
	dae::GameObject* CreateLiveText(const Vector2& pos, Lives* pLives);
	dae::GameObject* CreateScoreText(const Vector2& pos, Score* pScore);
	dae::GameObject* CreateDiamond(const Vector2& pos, const std::function<void()>& func, dae::Scene* pScene);
	dae::GameObject* CreateHighScoreList(const Vector2& pos, const std::string& filepath, HighScore* pHighScore);
}