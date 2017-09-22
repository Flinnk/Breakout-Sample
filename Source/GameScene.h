#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "Scene.h"
#include "Level.h"
#include <vector>


class GameScene : public Scene {
public:
	GameScene();
	void OnEnter() override;
	void OnUpdate(float DeltaTime) override;
	void OnRender(const GameEngine::SpriteRenderer* Renderer) override;

	void OnExit() override;
	virtual ~GameScene();
private:

	Level LoadedLevel;
	const GameEngine::Texture *Background = nullptr;
	class Paddle* Player = nullptr;
	class Ball* BallObject = nullptr;
	int CurrentLevel = 0;
	
	void CheckCollisions();
};

#endif