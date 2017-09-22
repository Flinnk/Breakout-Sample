#include "Paddle.h"
#include <Core\Engine.h>
#include <Core\Input.h>
using namespace GameEngine;

Paddle::Paddle(GameEngine::Vector2 pos, GameEngine::Vector2 size, const GameEngine::Texture *sprite, GameEngine::Vector3 color, GameEngine::Vector2 velocity) : GameObject(pos,size,sprite,color)
{
	Velocity = velocity;
}

