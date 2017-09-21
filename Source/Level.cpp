#include "Level.h"
#include <sstream>
#include <fstream>
#include <Utils\ResourceManager.h>
#include <Math\Math.h>

using namespace GameEngine;

Level::Level() {}
Level::~Level()
{
	Bricks.clear();
}

void Level::Load(const char *FilePath, unsigned int LevelWidth, unsigned int LevelHeight)
{
	Bricks.clear();

	unsigned int TileType;
	std::string Line;
	std::ifstream Stream(FilePath);
	std::vector<std::vector<unsigned int>> Data;
	if (Stream)
	{
		while (std::getline(Stream, Line))
		{
			std::istringstream StringStream(Line);
			std::vector<unsigned int> Row;
			while (StringStream >> TileType)
				Row.push_back(TileType);
			Data.push_back(Row);
		}
		if (Data.size() > 0)
			this->Init(Data, LevelWidth, LevelHeight);
	}
}

void Level::Draw(const SpriteRenderer *renderer)
{
	for (Brick &Block : Bricks) {
		if (!Block.Destroyed)
			Block.Draw(renderer);
	}
}

bool Level::IsCompleted()
{
	return false;
}
void Level::Init(std::vector<std::vector<unsigned int>> TileData, unsigned int LevelWidth, unsigned int LevelHeight)
{
	unsigned int Height = TileData.size();
	unsigned int Width = TileData[0].size();
	float TileWidth = LevelWidth / static_cast<float>(Width);
	float TileHeight = LevelHeight / Height;
	const Texture* Texture = ResourceManager::GetInstance().GetTexture("brick");

	for (unsigned int y = 0; y < Height; ++y)
	{
		for (unsigned int x = 0; x < Width; ++x)
		{
			Vector2 Position(TileWidth * x, TileHeight * y);
			Vector2 Size(TileWidth, TileHeight);

			bool IsDestroyable = false;
			Vector3 Color = Vector3(1.0f, 1.0f, 1.0f);

			if (TileData[y][x] > BrickType::EMPTY) {
				if (TileData[y][x] == BrickType::SOLID)
				{
					Color = Vector3(0.8f, 0.8f, 0.7f);

				}
				else if (TileData[y][x] > BrickType::SOLID)
				{
					switch (TileData[y][x])
					{
					case BrickType::BLUE:
						Color = Vector3(0.2f, 0.5f, 0.8f);
						break;
					case BrickType::GREEN:
						Color = Vector3(0.0f, 1.0f, 0.0f);
						break;
					case BrickType::YELLOW:
						Color = Vector3(1.0f, 1.0f, 0.0f);
						break;
					case BrickType::ORANGE:
						Color = Vector3(1.0f, 0.5f, 0.0f);
						break;
					}
				}

				Brick Object(Position, Size, Texture, Color);
				Object.IsDestroyable = IsDestroyable;
				Bricks.push_back(Object);
			}
		}
	}
}