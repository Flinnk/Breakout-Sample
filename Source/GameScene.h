#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "Scene.h"
#include "Level.h"
#include <vector>
#include "Definitions.h"

enum class State {
	PLAYING,
	GAMEOVER,
	COMPLETED
};

class GameScene : public Breakout::Scene {
public:
	GameScene();
	void OnEnter() override;
	void OnUpdate(float DeltaTime) override;
	void OnRender(GameEngine::Renderer* Renderer) override;

	void OnExit() override;
	virtual ~GameScene();
private:

	void CheckCollisions();
	void BallReset();
	void RestartGame();

	//States
	void UpdatePlayingState(float DeltaTime);
	void RenderPlayingState(GameEngine::Renderer* Renderer);

	void UpdateGameOverState(float DeltaTime);
	void RenderGameOverState(GameEngine::Renderer* Renderer);

	void RenderCompletedState(GameEngine::Renderer* Renderer);

	std::vector<std::string> Levels;
	class GameEngine::CameraComponent* RenderCamera = nullptr;

	Level LoadedLevel;
	const GameEngine::Texture *Background = nullptr;
	const GameEngine::Texture *Panel = nullptr;

	class Paddle* Player = nullptr;
	class Ball* BallObject = nullptr;
	int CurrentLevel = 0;
	int Credits = INITIAL_CREDITS;
	int Score = 0;
	State CurrentState = State::PLAYING;

};

#endif