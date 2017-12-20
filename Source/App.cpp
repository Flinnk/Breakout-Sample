#include "App.h"
#include <iostream>
#include "IntroScene.h"


App::App() {}
App::~App() {}

using namespace GameEngine;

void App::OnInitialize()
{
	IGraphicContext* GC = Engine::GetInstance().GetGraphicContext();
	GC->Init("Breakout",DisplayMode::WINDOWED, 640, 528);
	CurrentScene = new IntroScene();
	Engine::GetInstance().SetTargetFPS(120);
}

void App::OnBegin()
{
	CurrentScene->OnEnter();
}

void App::OnBeginFrame()
{
	if (NextScene != nullptr)
	{
		CurrentScene = NextScene;
		CurrentScene->OnEnter();
		NextScene = nullptr;
	}
}

void App::OnUpdate(float DeltaSeconds)
{
	CurrentScene->OnUpdate(DeltaSeconds);
}

void App::OnRender(Renderer* Renderer)
{
	CurrentScene->OnRender(Renderer);
}

void App::OnEndFrame()
{
	if (NextScene != nullptr)
	{
		CurrentScene->OnExit();
		delete CurrentScene;
		CurrentScene = nullptr;
		SoundManager::GetInstance().StopAll();
	}
}


void App::OnEnd()
{
	Log("End");
	if (CurrentScene)
		CurrentScene->OnExit();
	delete CurrentScene;
	CurrentScene = nullptr;
}

void App::LoadScene(Breakout::Scene* NewScene)
{
	NextScene = NewScene;
}
