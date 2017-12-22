#include "IntroScene.h"
#include "Breakout.h"
#include "App.h"
#include "GameScene.h"
#include <Engine\Core\Transform.h>
#include <Engine\Renderer\Camera.h>


IntroScene::IntroScene()
{

}

void IntroScene::OnEnter()
{
	ResourceManager& RManager = ResourceManager::GetInstance();
	Background = RManager.LoadTexture(RManager.GetResourceDirectory() + "Textures\\background.png", "background");
	SoundManager::GetInstance().PlaySound((RManager.GetResourceDirectory() + "Sound\\loop3.mp3").c_str(), true);

}

void IntroScene::OnUpdate(float DeltaTime)
{
	if (Input::GetKeyDown(Keyboard::ENTER))
	{
		App* AppInstance = static_cast<App*>(Engine::GetInstance().GetRunningApplicationInstance());
		AppInstance->LoadScene(new GameScene());
	}
}

void IntroScene::OnRender(Renderer* Renderer)
{

	Vector2 Size = Engine::GetInstance().GetDisplaySize();
	Transform CameraTransform;
	Camera CameraData;
	CameraData.NearPlane = -1.0f;
	CameraData.FarPlane = 1000.0f;
	CameraData.Mode = CameraMode::ORTHOGRAPHIC;
	CameraData.FieldOfView = 90.0f;
	Renderer->SetCameraData(&CameraData);
	Renderer->SetCameraTransform(&CameraTransform);
	Renderer->DrawTexture(Background, Vector2(0, 0), Size, 0, Vector3(1.0, 1.0, 1.0));
	Renderer->DrawText(std::string("BREAKOUT"), 186, 100, 0.5f, Vector3(1.0f, 1.0f, 1.0f));
	Renderer->DrawText(std::string("PRESS ENTER TO START"), 140, 400, 0.3f, Vector3(1.0f, 1.0f, 1.0f));

}

void IntroScene::OnExit()
{

}

IntroScene::~IntroScene()
{

}