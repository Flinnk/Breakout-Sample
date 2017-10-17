#include "GameObject.h"
#include "Breakout.h"


GameObject::GameObject()
	: Position(0, 0), Size(1, 1), Color(1.0f, 1.0f, 1.0f), Rotation(0.0f), Sprite() { }

GameObject::GameObject(Vector2 pos, Vector2 size, const Texture* sprite, Vector3 color)
	: Position(pos), Size(size), Color(color), Rotation(0.0f), Sprite(sprite) { }

void GameObject::Draw(const Renderer *Renderer)
{
	Renderer->DrawTexture(Sprite, Position, Size, Rotation, Color);
}