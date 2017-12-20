#ifndef BREAKOUT_SCENE_H
#define BREAKOUT_SCENE_H

#include <Engine\Renderer\Renderer.h>

namespace Breakout 
{

	class Scene {

	public:

		virtual ~Scene() {};
		virtual void OnEnter() = 0;
		virtual void OnUpdate(float DeltaTime) = 0;
		virtual void OnRender(GameEngine::Renderer* Renderer) = 0;
		virtual void OnExit() = 0;

	};
}

#endif // !BREAKOUT_SCENE_H
