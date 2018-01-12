#include "GameScene.h"
#include "Breakout.h"
#include "Paddle.h"
#include "Ball.h"
#include <Engine\Core\Transform.h>
#include <Engine\Components\CameraComponent.h>


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

GameScene::GameScene()
{
	RenderCamera = new CameraComponent();
	Camera CameraData;
	CameraData.NearPlane = -1.0f;
	CameraData.FarPlane = 1000.0f;
	CameraData.Mode = CameraMode::ORTHOGRAPHIC;
	CameraData.FieldOfView = 90.0f;
	RenderCamera->SetCameraData(CameraData);
}

void GameScene::OnEnter()
{
	ResourceManager& RManager = ResourceManager::GetInstance();

	Levels.push_back(RManager.GetResourceDirectory() + "Levels\\one.lvl");
	Levels.push_back(RManager.GetResourceDirectory() + "Levels\\two.lvl");

	Background = RManager.LoadTexture("Textures\\background.png");
	Panel = RManager.LoadTexture("Textures\\panel.png");
	RManager.LoadTexture("Textures\\brick.png");
	RManager.LoadTexture("Textures\\paddle.png");
	RManager.LoadTexture("Textures\\ball.png");

	Vector2 Size = Engine::GetInstance().GetDisplaySize();

	Player = new Paddle(Vector2((Size.x / 2) - (PADDLE_SIZE.x / 2), (0 + PADDLE_SIZE.y)), PADDLE_SIZE, RManager.GetTexture("Textures\\paddle.png"), Vector3(1.0f, 1.0f, 1.0f), Vector2(1000, 0));
	Vector2 BallPosition = Player->Position + Vector2(PADDLE_SIZE.x / 2 - BALL_RADIUS, BALL_RADIUS * 2);
	Player->DrawOrder = 2;
	BallObject = new Ball(BallPosition, BALL_RADIUS, RManager.GetTexture("Textures\\ball.png"), Vector3(1.0f, 1.0f, 1.0f), Vector2(200.0f, 600.0f));
	BallObject->DrawOrder = 2;

	Size.y -= INFO_PANEL_HEIGHT;
	LoadedLevel.Load(Levels[CurrentLevel].c_str(), Size.x, Size.y * 0.5f);

	SoundManager::GetInstance().PlaySound((RManager.GetResourceDirectory() + "Sound\\gba1complete.mp3").c_str(), true);
}
void GameScene::OnUpdate(float DeltaTime)
{
	switch (CurrentState)
	{
	case State::PLAYING:
		UpdatePlayingState(DeltaTime);
		break;
	case State::COMPLETED:
		UpdateGameOverState(DeltaTime);
		break;
	case State::GAMEOVER:
		UpdateGameOverState(DeltaTime);
		break;
	}
}

void GameScene::UpdateGameOverState(float DeltaTime)
{
	if (Input::GetKeyDown(Keyboard::R))
	{
		RestartGame();
	}
}

void GameScene::UpdatePlayingState(float DeltaTime)
{
	Vector2 ScreenSize = Engine::GetInstance().GetDisplaySize();

	if (LoadedLevel.IsCompleted())
	{
		BallReset();
		++CurrentLevel;
		if (CurrentLevel < Levels.size()) {
			ScreenSize.y -= INFO_PANEL_HEIGHT;
			LoadedLevel.Load(Levels[CurrentLevel].c_str(), ScreenSize.x, ScreenSize.y * 0.5f);
		}
		else {
			CurrentState = State::COMPLETED;
			return;
		}
	}

	float velocity = Player->Velocity.x * DeltaTime;

	if (Input::GetKey(Keyboard::A))
	{
		if (Player->Position.x >= 0)
		{
			Player->Position.x -= velocity;
			if (BallObject->StickToPaddle)
				BallObject->Position.x -= velocity;
		}
	}

	if (Input::GetKey(Keyboard::D))
	{
		if (Player->Position.x <= ScreenSize.x - Player->Sprite->GetWidth())
		{
			Player->Position.x += velocity;
			if (BallObject->StickToPaddle)
				BallObject->Position.x += velocity;
		}
	}

	if (Input::GetKeyDown(Keyboard::SPACE))
	{
		BallObject->StickToPaddle = false;
	}

	if (!BallObject->StickToPaddle)
	{
		BallObject->ResolveMovement(DeltaTime);
		CheckCollisions();
	}


	if (BallObject->Position.y < 0 - BALL_RADIUS * 2)
	{
		BallReset();
		Score -= SCORE_DECREASE;
		Credits -= 1;
		if (Credits < 0)
		{
			Credits = 0;
			CurrentState = State::GAMEOVER;
		}
	}
}



void GameScene::BallReset()
{
	Vector2 Size = Engine::GetInstance().GetDisplaySize();

	Player->Position = Vector2((Size.x / 2) - (PADDLE_SIZE.x / 2), (0 + PADDLE_SIZE.y));

	BallObject->Position = Player->Position + Vector2(PADDLE_SIZE.x / 2 - BALL_RADIUS, BALL_RADIUS * 2);
	BallObject->StickToPaddle = true;
	BallObject->Velocity = Vector2(200.0f, 600.0f);
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
				if (LoadedLevel.DestroyBrick(brick))
				{
					Score += SCORE_INCREASE;
				}

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

		BallObject->Velocity.y = std::abs(BallObject->Velocity.y);
		SoundManager::GetInstance().PlaySound((ResourceManager::GetInstance().GetResourceDirectory() + "Sound\\click4.ogg").c_str(), false);

	}
}

void GameScene::RestartGame()
{
	CurrentState = State::PLAYING;
	Credits = INITIAL_CREDITS;
	CurrentLevel = 0;
	Score = 0;
	Vector2 Size = Engine::GetInstance().GetDisplaySize();

	Size.y -= INFO_PANEL_HEIGHT;
	LoadedLevel.Load(Levels[CurrentLevel].c_str(), Size.x, Size.y * 0.5f);
}

void GameScene::OnRender(Renderer* Renderer)
{

	switch (CurrentState)
	{
	case State::PLAYING:
		RenderPlayingState(Renderer);
		break;
	case State::GAMEOVER:
		RenderGameOverState(Renderer);
		break;
	case State::COMPLETED:
		RenderCompletedState(Renderer);
		break;
	}
}


void GameScene::RenderGameOverState(GameEngine::Renderer* Renderer)
{
	Vector2 Size = Engine::GetInstance().GetDisplaySize();
	Renderer->SetCamera(RenderCamera);


	DrawCall2D BackgroundDrawCall;
	BackgroundDrawCall.DrawCallIdentifier = (0 << 24) | (Background->GetID() << 8);
	BackgroundDrawCall.Texture = Background;
	BackgroundDrawCall.Color = Vector3(1, 1, 1);
	BackgroundDrawCall.Scale = Vector3(1, 1, 1);
	BackgroundDrawCall.UseTextureSize = false;
	BackgroundDrawCall.DrawWidth = Size.x;
	BackgroundDrawCall.DrawHeight = Size.y;
	BackgroundDrawCall.Postion = Vector3(0, 0, 0);
	BackgroundDrawCall.Region = TextureRegion(0, 0, 1, 1);
	Renderer->DrawSprite(BackgroundDrawCall);

	Renderer->End();
	Renderer->DrawText(std::string("Game Over!"), 120, 50, 0.8f, Vector3(1.0f, 1.0f, 1.0f));
	Renderer->DrawText(std::string("Level: " + std::to_string(CurrentLevel)), 230, 160, 0.5f, Vector3(1.0f, 1.0f, 1.0f));
	Renderer->DrawText(std::string("Score: " + std::to_string(Score)), 230, 240, 0.5f, Vector3(1.0f, 1.0f, 1.0f));
	Renderer->DrawText(std::string("Press R to play again"), 150, 500, 0.4f, Vector3(1.0f, 1.0f, 1.0f));
}

void  GameScene::RenderCompletedState(GameEngine::Renderer* Renderer)
{
	Vector2 Size = Engine::GetInstance().GetDisplaySize();
	Renderer->SetCamera(RenderCamera);


	DrawCall2D BackgroundDrawCall;
	BackgroundDrawCall.DrawCallIdentifier = (0 << 24) | (Background->GetID() << 8);
	BackgroundDrawCall.Texture = Background;
	BackgroundDrawCall.Color = Vector3(1, 1, 1);
	BackgroundDrawCall.Scale = Vector3(1, 1, 1);
	BackgroundDrawCall.UseTextureSize = false;
	BackgroundDrawCall.DrawWidth = Size.x;
	BackgroundDrawCall.DrawHeight = Size.y;
	BackgroundDrawCall.Postion = Vector3(0, 0, 0);
	BackgroundDrawCall.Region = TextureRegion(0, 0, 1, 1);
	Renderer->DrawSprite(BackgroundDrawCall);

	Renderer->End();
	Renderer->DrawText(std::string("Congratulations!"), 60, 50, 0.8f, Vector3(1.0f, 1.0f, 1.0f));
	Renderer->DrawText(std::string("You have beaten the game!"), 100, 150, 0.4f, Vector3(1.0f, 1.0f, 1.0f));
	Renderer->DrawText(std::string("Score: " + std::to_string(Score)), 210, 300, 0.5f, Vector3(1.0f, 1.0f, 1.0f));
	Renderer->DrawText(std::string("Press R to play again"), 150, 500, 0.4f, Vector3(1.0f, 1.0f, 1.0f));
}


void GameScene::RenderPlayingState(Renderer* Renderer)
{
	Renderer->SetCamera(RenderCamera);
	Vector2 Size = Engine::GetInstance().GetDisplaySize();

	Size.y -= INFO_PANEL_HEIGHT;
	Vector2 PanelSize(Size.x, INFO_PANEL_HEIGHT);

	DrawCall2D PanelDrawCall;
	PanelDrawCall.DrawCallIdentifier = (1 << 24) | (Panel->GetID() << 8);
	PanelDrawCall.Texture = Panel;
	PanelDrawCall.Color = Vector3(1, 1, 1);
	PanelDrawCall.Scale = Vector3(1, 1, 1);
	PanelDrawCall.Postion = Vector3(0, Size.y, 0);
	PanelDrawCall.UseTextureSize = false;
	PanelDrawCall.DrawWidth = Size.x;
	PanelDrawCall.DrawHeight = INFO_PANEL_HEIGHT;
	PanelDrawCall.Region = TextureRegion(0, 0, 1, 1);

	DrawCall2D BackgroundDrawCall;
	BackgroundDrawCall.DrawCallIdentifier = (0 << 24) | (Background->GetID() << 8);
	BackgroundDrawCall.Texture = Background;
	BackgroundDrawCall.Color = Vector3(1, 1, 1);
	BackgroundDrawCall.Scale = Vector3(1, 1, 1);
	BackgroundDrawCall.UseTextureSize = false;
	BackgroundDrawCall.DrawWidth = Size.x;
	BackgroundDrawCall.DrawHeight = Size.y;
	BackgroundDrawCall.Postion = Vector3(0, 0, 0);
	BackgroundDrawCall.Region = TextureRegion(0, 0, 1, 1);


	Renderer->DrawSprite(BackgroundDrawCall);
	Renderer->DrawSprite(PanelDrawCall);

	LoadedLevel.Draw(Renderer);
	BallObject->Draw(Renderer);
	Player->Draw(Renderer);

	Renderer->End();
	Renderer->DrawText(std::string("Level: " + std::to_string(CurrentLevel + 1)), 272, 12, 0.3f, Vector3(1.0f, 1.0f, 1.0f));
	Renderer->DrawText(std::string("Score: " + std::to_string(Score)), 24, 12, 0.3f, Vector3(1.0f, 1.0f, 1.0f));
	Renderer->DrawText(std::string("Credits: " + std::to_string(Credits)), 500, 12, 0.3f, Vector3(1.0f, 1.0f, 1.0f));
}


void GameScene::OnExit()
{


}

GameScene::~GameScene()
{
	if (Player)
		delete Player;
	Player = nullptr;

	if (BallObject)
		delete BallObject;
	BallObject = nullptr;

	if (RenderCamera)
		delete RenderCamera;
	RenderCamera = nullptr;
}