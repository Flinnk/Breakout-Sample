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


App::App() {}
App::~App() {}

using namespace GameEngine;

void App::OnInitialize()
{
	GraphicContext* GC = Engine::GetInstance().GetGraphicContext();
	GC->Init(800, 600, "Breakout");
}

void App::OnBegin()
{
	Log("Begin");
}

void App::OnUpdate(float DeltaSeconds)
{
	if (Input::IsKeyPressed(KEY_E))
	{
		LogFormat("Key Pressed: %d", KEY_E);
		ASSERT(Input::IsKeyPressed(KEY_E));

	}
	else
	{
		LogFormat("Update delta: %f", DeltaSeconds);
	}
}

void App::OnRender(const SpriteRenderer* Renderer)
{

}


void App::OnEnd()
{
	Log("End");
}