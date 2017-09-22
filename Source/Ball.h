
#ifndef BALL_H
#define BALL_H

#include "GameObject.h"
const float  BALL_RADIUS = 12.5f;

class Ball : public GameObject
{
public:
	float Radius=0.0f;
	bool StickToPaddle = true;
	GameEngine::Vector2 Velocity;
	Ball(GameEngine::Vector2 pos, float radius, const GameEngine::Texture *sprite, GameEngine::Vector3 color = GameEngine::Vector3(1.0f, 1.0f, 1.0f), GameEngine::Vector2 Velocity = GameEngine::Vector2(0, 0));
	void ResolveMovement(float DeltaTime);
};
#endif // !BALL_H
