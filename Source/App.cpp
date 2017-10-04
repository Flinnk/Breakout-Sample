#include "App.h"
#include <Math\Math.h>
#include <iostream>
#include <Core\GraphicContext.h>
#include <Core\Engine.h>
#include <Core\Input.h>
#include <Utils\Log.h>
#include <Utils\Assert.h>
#include <Utils\ResourceManager.h>
#include <Renderer\SpriteRenderer.h>
#include "IntroScene.h"
#include <Audio\SoundManager.h>


App::App() {}
App::~App() {}

using namespace GameEngine;

void App::OnInitialize()
{
	GraphicContext* GC = Engine::GetInstance().GetGraphicContext();
	GC->Init(640, 528, "Breakout");
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

void App::OnRender(const Renderer* Renderer)
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

void App::LoadScene(Scene* NewScene)
{
	NextScene = NewScene;
}
