#include "GameObject.h"
#include "Breakout.h"


GameObject::GameObject()
	: Position(0, 0), Size(1, 1), Color(1.0f, 1.0f, 1.0f), Rotation(0.0f), Sprite() { }

GameObject::GameObject(Vector2 pos, Vector2 size, const Texture* sprite, Vector3 color)
	: Position(pos), Size(size), Color(color), Rotation(0.0f), Sprite(sprite) { }

void GameObject::Draw(const Renderer *Renderer)
{
	DrawCall2D DrawCall;
	DrawCall.DrawCallIdentifier = (DrawOrder<<24)|(Sprite->GetID()<<8);
	DrawCall.Texture = Sprite;
	DrawCall.Color = Color;
	DrawCall.Scale = Vector3(1,1,1);
	DrawCall.Postion = Position;
	DrawCall.UseTextureSize = false;
	DrawCall.DrawWidth = Size.x;
	DrawCall.DrawHeight = Size.y;
	DrawCall.Region = TextureRegion(0, 0, 1, 1);
	Renderer->DrawSprite(DrawCall);
}