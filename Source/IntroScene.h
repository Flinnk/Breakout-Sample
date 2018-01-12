#ifndef INTRO_SCENE_H
#define INTRO_SCENE_H

#include "Scene.h"
class IntroScene : public Breakout::Scene {
public:
	IntroScene();
	void OnEnter() override;
	void OnUpdate(float DeltaTime) override;
	void OnRender(GameEngine::Renderer* Renderer) override;

	void OnExit() override;
	virtual ~IntroScene();
private:

	const GameEngine::Texture *Background = nullptr;
	class GameEngine::CameraComponent* RenderCamera = nullptr;
};

#endif