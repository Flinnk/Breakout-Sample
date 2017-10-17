#include "Paddle.h"
#include "Breakout.h"


Paddle::Paddle(Vector2 pos, Vector2 size, const Texture *sprite, Vector3 color, Vector2 velocity) : GameObject(pos,size,sprite,color)
{
	Velocity = velocity;
}

