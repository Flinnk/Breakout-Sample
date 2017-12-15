
#ifndef PADDLE_H
#define PADDLE_H

#include "GameObject.h"
#include <Engine\Math\Math.h>
const GameEngine::Vector2 PADDLE_SIZE = GameEngine::Vector2(100, 20);

class Paddle : public GameObject
{
public:
	GameEngine::Vector2 Velocity;
	Paddle(GameEngine::Vector2 pos, GameEngine::Vector2 size, const GameEngine::Texture *sprite, GameEngine::Vector3 color = GameEngine::Vector3(1.0f, 1.0f, 1.0f), GameEngine::Vector2 Velocity = GameEngine::Vector2(0,0));
};
#endif // !PADDLE_H
