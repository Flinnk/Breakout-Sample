#include "Ball.h"
#include "Breakout.h"
#include "Definitions.h"

Ball::Ball(Vector2 pos, float radius, const Texture *sprite, Vector3 color , Vector2 velocity) : GameObject(pos, Vector2(radius * 2, radius * 2),sprite,color)
{
	Velocity = velocity;
	Radius = BALL_RADIUS;
}

void Ball::ResolveMovement(float DeltaTime) 
{
	Vector2 ScreenSize = Engine::GetInstance().GetDisplaySize();

	Position += Velocity * DeltaTime;
	if (Position.x <= 0.0f)
	{
		Velocity.x = -Velocity.x;
		Position.x = 0.0f;
	}
	else if (Position.x + Size.x >= ScreenSize.x)
	{
		Velocity.x = -Velocity.x;
		Position.x = ScreenSize.x - Size.x;
	}
	if (Position.y <= INFO_PANEL_HEIGHT)
	{
		Velocity.y = -Velocity.y;
		Position.y = INFO_PANEL_HEIGHT;
	}
}
