#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class APlayer : public AActor
{
public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	static APlayer* Ball;

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void MoveFunction(FVector2D _Dir);

	//void LeftMove(float _DeltaTime);
	//void RightMove(float _DeltaTime);
	//void UpMove(float _DeltaTime);
	//void DownMove(float _DeltaTime);

	FVector2D Dir = { 1.f , -1.f };
	
protected:

private:
	float Speed = 800.0f;

};

