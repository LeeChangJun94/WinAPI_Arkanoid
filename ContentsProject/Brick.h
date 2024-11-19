#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineSerializer.h>

enum class EBrickType
{
	WHITE,
	ORANGE,
	SKYBLUE,
	GREEN,
	RED,
	BLUE,
	PINK,
	YELLOW,
	SILVER,
	GOLD,
};


class APlayer;
class APlayerLife;
class ABall;
class U2DCollision;

// 설명 :
class ABrick : public AActor, public ISerializObject
{
public:
		// constrcuter destructer
	ABrick();
	~ABrick();

	// delete Function
	ABrick(const ABrick& _Other) = delete;
	ABrick(ABrick&& _Other) noexcept = delete;
	ABrick& operator=(const ABrick& _Other) = delete;
	ABrick& operator=(ABrick&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetBrickSize(FVector2D _Size)
	{
		SpriteRenderer->SetComponentScale(_Size);
	}



	//bool RectCheck();
	//EReflectionDir ReflectionDirCheck();

	//void SetBall(ABall* _Ball)
	//{
	//	Ball = _Ball;
	//}

	//ABall* GetBallActor()
	//{
	//	return this->BallActor;
	//}

	//ModeState ItemStats;
	inline void SetPlayerLife(APlayerLife* _Player) { PlayerLife = _Player; }

	void BrickDestroyCheck();
	void BallReflect(FVector2D _Vector);


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

	void SetBrickType(EBrickType _BrickType)
	{
		BrickType = _BrickType;
	}

	EBrickType GetBrickType()
	{
		return BrickType;
	}

	// 데이터를 직렬화(압축)
	void Serialize(UEngineSerializer& _Ser) override;
	// 데이터를 복구(할때)
	void DeSerialize(UEngineSerializer& _Ser) override;




protected:

private:
	
	FTransform BallTrans;

	FTransform BrickTrans;
	
	USpriteRenderer* SpriteRenderer;

	float Ratio = 0;
	float Line = 0;

	int Score = 0;
	int BrickHP = 0;
	EBrickType BrickType;
	bool CollisionCheck = false;
	
	U2DCollision* CollisionComponent = nullptr;

	APlayer* Vaus = nullptr;
	ABall* ResultBall = nullptr;
	APlayerLife* PlayerLife = nullptr;
};

