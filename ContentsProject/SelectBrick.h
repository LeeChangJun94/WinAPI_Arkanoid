#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineSerializer.h>


class APlayer;
class APlayerLife;
class ABall;
class U2DCollision;

// Ό³Έν :
class ASelectBrick : public AActor, public ABrick
{
public:
	// constrcuter destructer
	ASelectBrick();
	~ASelectBrick();

	// delete Function
	ASelectBrick(const ASelectBrick& _Other) = delete;
	ASelectBrick(ASelectBrick&& _Other) noexcept = delete;
	ASelectBrick& operator=(const ASelectBrick& _Other) = delete;
	ASelectBrick& operator=(ASelectBrick&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	inline void SetPlayerLife(APlayerLife* _Player) { PlayerLife = _Player; }

	void WhiteBrick();
	void OrangeBrick();
	void SkyBlueBrick();
	void GreenBrick();
	void RedBrick();
	void BlueBrick();
	void PinkBrick();
	void YellowBrick();
	void SilverBrick();
	void GoldBrick();

	void SetBrickType(ABrick::EBrickType _BrickType)
	{
		BrickType = _BrickType;
	}

protected:

private:
	USpriteRenderer* SpriteRenderer;
		
	int Score = 0;
	int BrickHP = 0;
	ABrick::EBrickType BrickType;
	
	U2DCollision* CollisionComponent = nullptr;

	APlayer* Vaus = nullptr;
	ABall* ResultBall = nullptr;
	APlayerLife* PlayerLife = nullptr;
};

