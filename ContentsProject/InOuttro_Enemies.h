#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class AInOuttro_Laser;
class AInOuttro_StarShip;

enum class EInOuttro_Enemies
{
	NONE,
	INTRO,
	OUTTRO,
};

// Ό³Έν :
class AInOuttro_Enemies : public AActor
{
public:
	// constrcuter destructer
	AInOuttro_Enemies();
	~AInOuttro_Enemies();

	// delete Function
	AInOuttro_Enemies(const AInOuttro_Enemies& _Other) = delete;
	AInOuttro_Enemies(AInOuttro_Enemies&& _Other) noexcept = delete;
	AInOuttro_Enemies& operator=(const AInOuttro_Enemies& _Other) = delete;
	AInOuttro_Enemies& operator=(AInOuttro_Enemies&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetStarShip(AInOuttro_StarShip* _StarShip)
	{
		StarShip = _StarShip;
	}

	void SetInOuttroType(EInOuttro_Enemies _EnemiesType)
	{
		EnemiesType = _EnemiesType;
	}

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	AInOuttro_Laser* Laser = nullptr;
	AInOuttro_StarShip* StarShip = nullptr;
	EInOuttro_Enemies EnemiesType = EInOuttro_Enemies::NONE;

	FVector2D Bezier = { 0, 0 };

	FVector2D P0 = { 333, 126 };
	FVector2D P1 = { 750, 60 };
	FVector2D P2 = { 750, 750 };
	FVector2D P3 = { 60, 200 };

	float CheckTime = 0.0f;
	//float OuttroCheckTime = 1.0f;
};

