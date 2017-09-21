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
#include "GameScene.h"

App::App() {}
App::~App() {}

using namespace GameEngine;

void App::OnInitialize()
{
	GraphicContext* GC = Engine::GetInstance().GetGraphicContext();
	GC->Init(800, 600, "Breakout");
	CurrentScene = new GameScene();
	Engine::GetInstance().SetTargetFPS(60);
}

void App::OnBegin()
{
	Log("Begin");
	CurrentScene->OnEnter();
}

void App::OnUpdate(float DeltaSeconds)
{
	CurrentScene->OnUpdate(DeltaSeconds);
	LogFormat("Update %d", Engine::GetInstance().GetFpsStat());
}

void App::OnRender(const SpriteRenderer* Renderer)
{
	CurrentScene->OnRender(Renderer);
}


void App::OnEnd()
{
	Log("End");
	if (CurrentScene)
		CurrentScene->OnExit();
	delete CurrentScene;
	CurrentScene = nullptr;
}