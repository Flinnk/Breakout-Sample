#include "GameScene.h"
#include <Math\Math.h>
#include <Core\Engine.h>
#include <Utils\ResourceManager.h>

using namespace GameEngine;
GameScene::GameScene() {}

void GameScene::OnEnter() 
{
	Background = ResourceManager::GetInstance().LoadTexture("D:\\Desarrollo\\C-C++\\Breakout-Sample\\Resources\\Textures\\background.png", "background");
	ResourceManager::GetInstance().LoadTexture("D:\\Desarrollo\\C-C++\\Breakout-Sample\\Resources\\Textures\\brick.png", "brick");

	Vector2 Size = Engine::GetInstance().GetDisplaySize();

	LoadedLevel.Load("D:\\Desarrollo\\C-C++\\Breakout-Sample\\Resources\\Levels\\one.lvl", Size.x, Size.y * 0.5);
}
void GameScene::OnUpdate(float DeltaTime) 
{

}

void GameScene::OnRender(const GameEngine::SpriteRenderer* Renderer) 
{
	Vector2 Size = Engine::GetInstance().GetDisplaySize();

	Renderer->DrawTexture(Background, Vector2(0, 0), Size, 0,Vector3(1.0,1.0,1.0));
	LoadedLevel.Draw(Renderer);
}
void GameScene::OnExit() {}
GameScene::~GameScene() {}