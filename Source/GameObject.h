#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Math\Math.h>
#include <Renderer\Texture.h>
#include <Renderer\SpriteRenderer.h>
class GameObject 
{
public:
	GameEngine::Vector2   Position, Size;
	GameEngine::Vector3   Color;
	float     Rotation;

	const GameEngine::Texture* Sprite = nullptr;

	GameObject();
	GameObject(GameEngine::Vector2 pos, GameEngine::Vector2 size, const GameEngine::Texture *sprite, GameEngine::Vector3 color = GameEngine::Vector3(1.0f, 1.0f, 1.0f));

	virtual void Draw(const GameEngine::SpriteRenderer *renderer);
};

#endif // !GAMEOBJECT_H
