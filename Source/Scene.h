#ifndef SCENE_H
#define SCENE_H

#include <Engine\Renderer\Renderer.h>

class Scene {

public:

	virtual ~Scene() {};
	virtual void OnEnter() = 0;
	virtual void OnUpdate(float DeltaTime) = 0;
	virtual void OnRender(GameEngine::Renderer* Renderer)=0;
	virtual void OnExit() = 0;

};

#endif // !SCENE_H
