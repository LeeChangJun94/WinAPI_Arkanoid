#pragma once
#include <EngineCore/GameMode.h>
#include <vector>

#include "TileMap.h"
#include "Brick.h"

// Ό³Έν :
class APlayGameMode : public AGameMode
{
public:
	// constrcuter destructer
	APlayGameMode();
	~APlayGameMode();

	// delete Function
	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

	void BeginPlay();

	std::list<ABrick*> BrickPtr;

protected:

private:
	//FVector2D BrickScale = { 32, 16 };
	//ATileMap* BrickTileMap = nullptr;
	//AScore* Score = nullptr;


};

