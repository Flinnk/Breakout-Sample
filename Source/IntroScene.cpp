#include "IntroScene.h"
#include "Breakout.h"
#include "App.h"
#include "GameScene.h"
#include <Engine\Core\Transform.h>
#include <Engine\Components\CameraComponent.h>
#include <Engine\Renderer\Camera.h>

IntroScene::IntroScene()
{
	RenderCamera = new CameraComponent();
	Camera CameraData;
	CameraData.NearPlane = -1.0f;
	CameraData.FarPlane = 1000.0f;
	CameraData.Mode = CameraMode::ORTHOGRAPHIC;
	RenderCamera->SetCameraData(CameraData);
}

void IntroScene::OnEnter()
{
	ResourceManager& RManager = ResourceManager::GetInstance();
	Background = RManager.LoadTexture("Textures\\background.png");
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
	Renderer->SetCamera(RenderCamera);

	DrawCall2D DrawCall;
	DrawCall.DrawCallIdentifier = Background->GetID();
	DrawCall.Texture = Background;
	DrawCall.Postion = Vector3(0,0, 0);
	DrawCall.Scale = Vector3(1,1, 1);
	DrawCall.Color = Vector3(1, 1, 1);
	DrawCall.Region = TextureRegion(0, 0, 1, 1);
	DrawCall.UseTextureSize = false;
	DrawCall.DrawWidth = Size.x;
	DrawCall.DrawHeight = Size.y;

	Renderer->DrawSprite(DrawCall);
	Renderer->End();//Temp hack to flush batch calls, until text is integrated in the batch renderer
	Renderer->DrawText(std::string("BREAKOUT"), 186, 100, 0.5f, Vector3(1.0f, 1.0f, 1.0f));
	Renderer->DrawText(std::string("PRESS ENTER TO START"), 140, 400, 0.3f, Vector3(1.0f, 1.0f, 1.0f));

}

void IntroScene::OnExit()
{

}

IntroScene::~IntroScene()
{
	if (RenderCamera)
		delete RenderCamera;
	RenderCamera = nullptr;
}