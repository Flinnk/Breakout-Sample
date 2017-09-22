#include "GameScene.h"
#include <Math\Math.h>
#include <Core\Engine.h>
#include <Core\Input.h>
#include <Utils\ResourceManager.h>
#include <Physics\SandboxPhysics.h>
#include "Paddle.h"
#include "Ball.h"
using namespace GameEngine;
GameScene::GameScene() {}

void GameScene::OnEnter() 
{
	Background = ResourceManager::GetInstance().LoadTexture("D:\\Desarrollo\\C-C++\\Breakout-Sample\\Resources\\Textures\\background.png", "background");
	ResourceManager::GetInstance().LoadTexture("D:\\Desarrollo\\C-C++\\Breakout-Sample\\Resources\\Textures\\brick.png", "brick");
	ResourceManager::GetInstance().LoadTexture("D:\\Desarrollo\\C-C++\\Breakout-Sample\\Resources\\Textures\\paddle.png", "paddle");
	ResourceManager::GetInstance().LoadTexture("D:\\Desarrollo\\C-C++\\Breakout-Sample\\Resources\\Textures\\ball.png", "ball");

	Vector2 Size = Engine::GetInstance().GetDisplaySize();

	Player = new Paddle(Vector2((Size.x / 2) - (PADDLE_SIZE.x / 2), (Size.y - PADDLE_SIZE.y)), PADDLE_SIZE, ResourceManager::GetInstance().GetTexture("paddle"), Vector3(1.0f, 1.0f, 1.0f),Vector2(10000,0));
	
	Vector2 BallPosition = Player->Position + Vector2(PADDLE_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);

	BallObject = new Ball(BallPosition, BALL_RADIUS, ResourceManager::GetInstance().GetTexture("ball"), Vector3(1.0f, 1.0f, 1.0f), Vector2(2000.0f, -7000.0f));
	LoadedLevel.Load("D:\\Desarrollo\\C-C++\\Breakout-Sample\\Resources\\Levels\\one.lvl", Size.x, Size.y * 0.5);
}
void GameScene::OnUpdate(float DeltaTime) 
{
	Vector2 ScreenSize = Engine::GetInstance().GetDisplaySize();

	float velocity = Player->Velocity.x * DeltaTime;

	if (Input::IsKeyPressed(KEY_A))
	{
		if (Player->Position.x >= 0)
		{
			Player->Position.x -= velocity;
			if (BallObject->StickToPaddle)
				BallObject->Position.x -= velocity;
		}
	}

	if (Input::IsKeyPressed(KEY_D))
	{
		if (Player->Position.x <= ScreenSize.x - Player->Size.x)
		{
			Player->Position.x += velocity;
			if (BallObject->StickToPaddle)
				BallObject->Position.x += velocity;
		}
	}

	if (Input::IsKeyPressed(KEY_SPACE) ) 
	{
		BallObject->StickToPaddle = false;
	}

	if (!BallObject->StickToPaddle)
	{
		BallObject->ResolveMovement(DeltaTime);
	}

	CheckCollisions();

	if (BallObject->Position.y >= ScreenSize.y)
	{
		//GameOver
	}
}

void GameScene::CheckCollisions()
{
	for (Brick &brick : LoadedLevel.Bricks)
	{
		if (!brick.Destroyed)
		{
			if (Collision::CheckCollision(Circle(BallObject->Position.x, BallObject->Position.y, BallObject->Radius), Rect(brick.Position.x, brick.Position.y, brick.Size.x, brick.Size.y)))
			{
				if (brick.IsDestroyable)
					brick.Destroyed = true;
			}
		}
	}
}

void GameScene::OnRender(const GameEngine::SpriteRenderer* Renderer) 
{
	Vector2 Size = Engine::GetInstance().GetDisplaySize();

	Renderer->DrawTexture(Background, Vector2(0, 0), Size, 0,Vector3(1.0,1.0,1.0));
	LoadedLevel.Draw(Renderer);
	BallObject->Draw(Renderer);
	Player->Draw(Renderer);
}

void GameScene::OnExit()
{
	delete Player;
	Player = nullptr;
	delete BallObject;
	BallObject = nullptr;
}

GameScene::~GameScene() {}