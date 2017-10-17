#include "Brick.h"
#include "Breakout.h"

Brick::Brick() {

}

Brick::~Brick(){}

Brick::Brick(Vector2 pos, Vector2 size, const Texture *sprite, Vector3 color) : GameObject(pos, size, sprite, color)
{
}
