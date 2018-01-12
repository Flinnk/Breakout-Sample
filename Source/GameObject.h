#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Engine\Math\Math.h>
#include <Engine\Graphics\Texture.h>
#include <Engine\Renderer\Renderer.h>
class GameObject 
{
public:
	GameEngine::Vector2   Position, Size;
	GameEngine::Vector3   Color;
	float     Rotation;
	int DrawOrder = 0;

	const GameEngine::Texture* Sprite = nullptr;

	GameObject();
	GameObject(GameEngine::Vector2 pos, GameEngine::Vector2 size, const GameEngine::Texture *sprite, GameEngine::Vector3 color = GameEngine::Vector3(1.0f, 1.0f, 1.0f));

	virtual void Draw(const GameEngine::Renderer *renderer);
};

#endif // !GAMEOBJECT_H
