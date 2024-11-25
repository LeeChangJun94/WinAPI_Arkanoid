#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;

// Ό³Έν :
class AIntro_Laser : public AActor
{
public:
	// constrcuter destructer
	AIntro_Laser();
	~AIntro_Laser();

	// delete Function
	AIntro_Laser(const AIntro_Laser& _Other) = delete;
	AIntro_Laser(AIntro_Laser&& _Other) noexcept = delete;
	AIntro_Laser& operator=(const AIntro_Laser& _Other) = delete;
	AIntro_Laser& operator=(AIntro_Laser&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
	USpriteRenderer* SpriteRenderer1 = nullptr;
	USpriteRenderer* SpriteRenderer2 = nullptr;

};

