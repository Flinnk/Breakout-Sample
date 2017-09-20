#ifndef APP_H
#define APP_H

#include <Core\Application.h> 

class App : public GameEngine::Application 
{

public:

	App();
	virtual ~App();

	virtual void OnInitialize() override;
	virtual void OnBegin() override;
	virtual void OnUpdate(float DeltaSeconds) override;
	virtual void OnRender(const class GameEngine::SpriteRenderer* Renderer) override;
	virtual void OnEnd() override;

};

#endif // !APP_H
