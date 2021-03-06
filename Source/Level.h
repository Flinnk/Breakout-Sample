#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Brick.h"
class Level {

public:
	std::vector<Brick> Bricks;

	Level();
	~Level();

	void Load(const char *FilePath, unsigned int LevelWidth, unsigned int LevelHeight);

	void Draw(const GameEngine::Renderer *renderer);

	bool IsCompleted();

	bool DestroyBrick(Brick& CollisionedBrick);
private:

	int RemainingBricks = 0;
	void Init(std::vector<std::vector<unsigned int>> TileData, unsigned int LevelWidth, unsigned int LevelHeight);


};
#endif // !LEVEL_H
