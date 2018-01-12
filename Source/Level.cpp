#include "Level.h"
#include <sstream>
#include <fstream>
#include "Breakout.h"
#include "Definitions.h"


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

void Level::Draw(const Renderer *renderer)
{
	for (Brick &Block : Bricks) {
		if (!Block.Destroyed)
			Block.Draw(renderer);
	}
}

bool Level::IsCompleted()
{
	return RemainingBricks <= 0;
}
void Level::Init(std::vector<std::vector<unsigned int>> TileData, unsigned int LevelWidth, unsigned int LevelHeight)
{
	RemainingBricks = 0;
	Vector2 Size = Engine::GetInstance().GetDisplaySize();
	unsigned int Height = TileData.size();
	unsigned int Width = TileData[0].size();
	float TileWidth = LevelWidth / static_cast<float>(Width);
	float TileHeight = LevelHeight / Height;
	const Texture* Texture = ResourceManager::GetInstance().GetTexture("Textures\\brick.png");

	Size.y -= INFO_PANEL_HEIGHT+TileHeight;


	for (unsigned int y = 0; y < Height; ++y)
	{
		for (unsigned int x = 0; x < Width; ++x)
		{
			Vector2 Position(TileWidth * x, Size.y - (TileHeight * y));
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
					IsDestroyable = true;
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
					++RemainingBricks;

				}

				Brick Object(Position, Size, Texture, Color);
				Object.DrawOrder = 3;
				Object.IsDestroyable = IsDestroyable;
				Bricks.push_back(Object);
			}
		}

	}
}

bool Level::DestroyBrick(Brick& CollisionedBrick)
{
	if (CollisionedBrick.IsDestroyable && !CollisionedBrick.Destroyed)
	{
		CollisionedBrick.Destroyed = true;
		SoundManager::GetInstance().PlaySound((ResourceManager::GetInstance().GetResourceDirectory() + "Sound\\Collect_Point_01.wav").c_str(), false);
		--RemainingBricks;
		return true;
	}
	else if (!CollisionedBrick.IsDestroyable)
	{
		SoundManager::GetInstance().PlaySound((ResourceManager::GetInstance().GetResourceDirectory() + "Sound\\click4.ogg").c_str(), false);
		return false;
	}
}