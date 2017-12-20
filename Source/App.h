#ifndef APP_H
#define APP_H

#include <Engine\Engine.h> 
#include "Scene.h"

class App : public GameEngine::Application 
{

public:

	App();
	virtual ~App();

	virtual void OnInitialize() override;
	virtual void OnBegin() override;
	virtual void OnBeginFrame() override;
	virtual void OnUpdate(float DeltaSeconds) override;
	virtual void OnRender(class GameEngine::Renderer* Renderer) override;
	virtual void OnEndFrame() override;

	virtual void OnEnd() override;

	void LoadScene(Breakout::Scene* NewScene);
private:
	Breakout::Scene* CurrentScene = nullptr;
	Breakout::Scene* NextScene = nullptr;
};

#endif // !APP_H
