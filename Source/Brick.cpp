#include "Brick.h"

Brick::Brick() {

}

Brick::~Brick(){}

Brick::Brick(GameEngine::Vector2 pos, GameEngine::Vector2 size, const GameEngine::Texture *sprite, GameEngine::Vector3 color) : GameObject(pos, size, sprite, color)
{
}
