#include "GameScene.h"
#include <Math\Math.h>
#include <Core\Engine.h>
#include <Core\Input.h>
#include <Utils\ResourceManager.h>
#include <Physics\SandboxPhysics.h>
#include "Paddle.h"
#include "Ball.h"
#include <Audio\SoundManager.h>
#include <Utils\Log.h>

using namespace GameEngine;


enum CollisionDirection {
	LEFT = 0,
	RIGHT,
	UP,
	DOWN
};

CollisionDirection ObtainDirection(Vector2 vector)
{
	//Same order as enum
	Vector2 DirectionVectors[] = {
		Vector2(-1.0f, 0.0f),
		Vector2(1.0f, 0.0f),
		Vector2(0.0f, 1.0f),
		Vector2(0.0f, -1.0f)
	};
	float max = 0.0f;
	int index = -1;
	for (int i = 0; i < 4; i++)
	{
		float Dot = vector.Normalize().Dot(DirectionVectors[i]);
		if (Dot > max)
		{
			max = Dot;
			index = i;
		}
	}
	return (CollisionDirection)index;
}

GameScene::GameScene() {}

void GameScene::OnEnter()
{
	Background = ResourceManager::GetInstance().LoadTexture("D:\\Desarrollo\\C-C++\\Breakout-Sample\\Resources\\Textures\\background.png", "background");
	ResourceManager::GetInstance().LoadTexture("D:\\Desarrollo\\C-C++\\Breakout-Sample\\Resources\\Textures\\brick.png", "brick");
	ResourceManager::GetInstance().LoadTexture("D:\\Desarrollo\\C-C++\\Breakout-Sample\\Resources\\Textures\\paddle.png", "paddle");
	ResourceManager::GetInstance().LoadTexture("D:\\Desarrollo\\C-C++\\Breakout-Sample\\Resources\\Textures\\ball.png", "ball");

	Vector2 Size = Engine::GetInstance().GetDisplaySize();

	Player = new Paddle(Vector2((Size.x / 2) - (PADDLE_SIZE.x / 2), (Size.y - PADDLE_SIZE.y)), PADDLE_SIZE, ResourceManager::GetInstance().GetTexture("paddle"), Vector3(1.0f, 1.0f, 1.0f), Vector2(1000, 0));

	Vector2 BallPosition = Player->Position + Vector2(PADDLE_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);

	BallObject = new Ball(BallPosition, BALL_RADIUS, ResourceManager::GetInstance().GetTexture("ball"), Vector3(1.0f, 1.0f, 1.0f), Vector2(200.0f, -700.0f));
	LoadedLevel.Load(Levels[CurrentLevel], Size.x, Size.y * 0.5f);

	SoundManager::GetInstance().PlaySound("D:\\Desarrollo\\C-C++\\Breakout-Sample\\Resources\\Sound\\gba1complete.mp3", true);
}
void GameScene::OnUpdate(float DeltaTime)
{

	Vector2 ScreenSize = Engine::GetInstance().GetDisplaySize();

	if (LoadedLevel.IsCompleted())
	{
		BallReset();
		++CurrentLevel;
		if (CurrentLevel < NUM_LEVELS) {
			LoadedLevel.Load(Levels[CurrentLevel], ScreenSize.x, ScreenSize.y * 0.5f);
		}
		else {
			Log("Finish"); //TODO: Temp
			return;
		}
	}

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

	if (Input::IsKeyPressed(KEY_SPACE))
	{
		BallObject->StickToPaddle = false;
	}

	if (!BallObject->StickToPaddle)
	{
		BallObject->ResolveMovement(DeltaTime);
		CheckCollisions();
	}


	if (BallObject->Position.y >= ScreenSize.y)
	{
		BallReset();
	}
}

void GameScene::BallReset()
{
	Vector2 Size = Engine::GetInstance().GetDisplaySize();

	Player->Position = Vector2((Size.x / 2) - (PADDLE_SIZE.x / 2), (Size.y - PADDLE_SIZE.y));

	BallObject->Position = Player->Position + Vector2(PADDLE_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
	BallObject->StickToPaddle = true;
	BallObject->Velocity = Vector2(200.0f, -700.0f);
}


void GameScene::CheckCollisions()
{

	//Check collision with bricks
	for (Brick &brick : LoadedLevel.Bricks)
	{
		if (!brick.Destroyed)
		{
			CollisionData data = CheckCollision(Circle(BallObject->Position.x, BallObject->Position.y, BallObject->Radius), Rect(brick.Position.x, brick.Position.y, brick.Size.x, brick.Size.y));
			if (data.Hit)
			{
				LoadedLevel.DestroyBrick(brick);

				CollisionDirection Direction = ObtainDirection(data.DifferenceVector);
				if (Direction == LEFT || Direction == RIGHT)
				{
					BallObject->Velocity.x = -BallObject->Velocity.x;

					float penetration = BallObject->Radius - std::abs(data.DifferenceVector.x);
					if (Direction == LEFT)
						BallObject->Position.x += penetration;
					else
						BallObject->Position.x -= penetration;
				}
				else
				{
					BallObject->Velocity.y = -BallObject->Velocity.y;

					float penetration = BallObject->Radius - std::abs(data.DifferenceVector.y);
					if (Direction == UP)
						BallObject->Position.y -= penetration;
					else
						BallObject->Position.y += penetration;
				}
			}
		}
	}

	//Check collision with paddle
	CollisionData hit = CheckCollision(Circle(BallObject->Position.x, BallObject->Position.y, BallObject->Radius), Rect(Player->Position.x, Player->Position.y, Player->Size.x, Player->Size.y));
	if (!BallObject->StickToPaddle && hit.Hit)
	{
		float centerBoard = Player->Position.x + Player->Size.x / 2;
		float distance = (BallObject->Position.x + BallObject->Radius) - centerBoard;
		float percentage = distance / (Player->Size.x / 2);

		float strength = 10.0f;
		Vector2 oldVelocity = BallObject->Velocity;
		BallObject->Velocity.x = 50.0f * percentage * strength;

		BallObject->Velocity = BallObject->Velocity.Normalize() * oldVelocity.Length();

		BallObject->Velocity.y = -1 * std::abs(BallObject->Velocity.y);
		SoundManager::GetInstance().PlaySound("D:\\Desarrollo\\C-C++\\Breakout-Sample\\Resources\\Sound\\click4.ogg", false);

	}
}

void GameScene::OnRender(const GameEngine::SpriteRenderer* Renderer)
{
	Vector2 Size = Engine::GetInstance().GetDisplaySize();

	Renderer->DrawTexture(Background, Vector2(0, 0), Size, 0, Vector3(1.0, 1.0, 1.0));
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