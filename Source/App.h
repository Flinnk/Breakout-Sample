#ifndef APP_H
#define APP_H

#include <Engine.h> 

class Scene;

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

	void LoadScene(Scene* NewScene);
private:
	Scene* CurrentScene = nullptr;
	Scene* NextScene = nullptr;
};

#endif // !APP_H
