#pragma once
#include <EngineCore/GameMode.h>
#include "Brick.h"

// Ό³Έν :
class ATileMapEditor : public AGameMode
{
public:
	// constrcuter destructer
	ATileMapEditor();
	~ATileMapEditor();

	// delete Function
	ATileMapEditor(const ATileMapEditor& _Other) = delete;
	ATileMapEditor(ATileMapEditor&& _Other) noexcept = delete;
	ATileMapEditor& operator=(const ATileMapEditor& _Other) = delete;
	ATileMapEditor& operator=(ATileMapEditor&& _Other) noexcept = delete;

	bool IndexOver(FIntPoint _TilePoint);

	void ClearBrick();

protected:
	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	U2DCollision* CollisionComponent = nullptr;
	std::vector<std::vector<ABrick*>> Bricks;
	ABrick* CurBrick = nullptr;
	EBrickType CurBrickType;
};

