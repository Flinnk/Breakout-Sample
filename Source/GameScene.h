#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "Scene.h"
#include "Level.h"
#include <vector>

class GameScene : public Breakout::Scene {
public:
	GameScene();
	void OnEnter() override;
	void OnUpdate(float DeltaTime) override;
	void OnRender(GameEngine::Renderer* Renderer) override;

	void OnExit() override;
	virtual ~GameScene();
private:

	Level LoadedLevel;
	const GameEngine::Texture *Background = nullptr;
	const GameEngine::Texture *Panel = nullptr;

	class Paddle* Player = nullptr;
	class Ball* BallObject = nullptr;
	int CurrentLevel = 0;
	int Score = 0;

	void CheckCollisions();
	void BallReset();

	std::vector<std::string> Levels;
};

#endif