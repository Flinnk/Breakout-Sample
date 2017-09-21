#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"

enum BrickType :int {
	EMPTY = 0,
	SOLID = 1,
	BLUE = 2,
	GREEN = 3,
	YELLOW = 4,
	ORANGE = 5
};

class Brick : public GameObject {

public:

	Brick();
	Brick(GameEngine::Vector2 pos, GameEngine::Vector2 size, const GameEngine::Texture *sprite, GameEngine::Vector3 color = GameEngine::Vector3(1.0f, 1.0f, 1.0f));
	~Brick();
	bool Destroyed = false;
	bool IsDestroyable = false;
};

#endif // !BRICK_H
