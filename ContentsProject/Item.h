#pragma once
#include <EngineCore/Actor.h>

class APlayer;
class APlayerLife;
class ABall;

enum class ModeState
{
	None,
	Slow,
	Catch,
	Laser,
	Enlarge,
	Disruption,
	Break,
	Player,
};


// Ό³Έν :
class AItem : public AActor
{
public:
	// constrcuter destructer
	AItem();
	~AItem();

	static AItem* Item;

	// delete Function
	AItem(const AItem& _Other) = delete;
	AItem(AItem&& _Other) noexcept = delete;
	AItem& operator=(const AItem& _Other) = delete;
	AItem& operator=(AItem&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	int ItemType = 0;

	void ItemSlow();
	void ItemSlowEffect();
	void ItemCatch();
	void ItemCatchEffect();
	void ItemLaser();
	void ItemLaserEffect();
	void ItemEnlarge();
	void ItemEnlargeEffect();
	void ItemDisruption();
	void ItemDisruptionEffect();
	void ItemBreak();
	void ItemBreakEffect();
	void ItemPlayer();
	void ItemPlayerEffect();

	void ItemCollisionCheck();

	void SetBall(ABall* _Ball)
	{
		Ball = _Ball;
	}

	//ABall* GetBallActor()
	//{
	//	return this->BallActor;
	//}

	ModeState RandomItemCreate();

	ModeState ItemState = ModeState::None;

	inline void SetPlayerLife(APlayerLife* _Player) { PlayerLife = _Player; }

protected:

private:
	float Speed = 200.0f;
	
	class USpriteRenderer* SpriteRenderer1 = nullptr;
	class USpriteRenderer* SpriteRenderer2 = nullptr;
	

	U2DCollision* CollisionComponent;

	APlayer* Vaus = nullptr;
	APlayerLife* PlayerLife = nullptr;;
	ABall* Ball = nullptr;

};

