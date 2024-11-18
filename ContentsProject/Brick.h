#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineSerializer.h>

enum class EReflectionDir
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	MAX,
};

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

class Tile : public ISerializObject
{
public:
	// �̷� Ŭ������ �����Ҷ�
	// ���� ���δ� �� �����ؾ� �Ѵ�.
	// ���߿��� ������°� ��������?
	// �����Լ� ���̺�
	USpriteRenderer* SpriteRenderer;

	bool IsMove = true;
	int TileType = -1;
	// Ÿ���ϳ��ϳ��� �������� ũ�⸦ ������ �ִٸ�
	// �̰ɷ� ���� �Է����ּž� �մϴ�.
	FVector2D Scale;
	FVector2D Pivot;
	int SpriteIndex;

	// �����͸� ����ȭ(����)
	void Serialize(UEngineSerializer& _Ser)
	{
		std::string SpriteName;
		if (nullptr != SpriteRenderer)
		{
			SpriteName = SpriteRenderer->GetCurSpriteName();
		}
		_Ser << SpriteName;
		_Ser << IsMove;
		_Ser << TileType;
		_Ser << Scale;
		_Ser << Pivot;
		_Ser << SpriteIndex;
	}

	void DeSerialize(UEngineSerializer& _Ser)
	{
		//std::string SpriteName;
		// _Ser >> SpriteName;

		// SpriteRenderer->SetSprite(SpriteName);

		std::string SpriteName;
		_Ser >> SpriteName;
		_Ser >> IsMove;
		_Ser >> TileType;
		_Ser >> Scale;
		_Ser >> Pivot;
		_Ser >> SpriteIndex;

	}

};

class APlayer;
class APlayerLife;
class ABall;
class U2DCollision;

// ���� :
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
	void BallReflect();


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

	void Create(std::string_view _Sprite, FIntPoint _Count, FVector2D _TileSize);

	void SetTileLocation(FVector2D _Location, int _SpriteIndex);

	void SetTileIndex(FIntPoint _Index, int _SpriteIndex);
	void SetTileIndex(FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, int _SpriteIndex);

	Tile* GetTileRef(FIntPoint _Index);
	Tile* GetTileRef(FVector2D _Location);

	FVector2D IndexToTileLocation(FIntPoint _Index);

	FIntPoint LocationToIndex(FVector2D _Location);

	bool IsIndexOver(FIntPoint _Index);

	// �����͸� ����ȭ(����)
	void Serialize(UEngineSerializer& _Ser);
	// �����͸� ����(�Ҷ�)
	void DeSerialize(UEngineSerializer& _Ser);











protected:

private:
	static FVector2D ReflectionVector[static_cast<int>(EReflectionDir::MAX)];
	
	FTransform BallTrans;

	FTransform BrickTrans;
	
	USpriteRenderer* SpriteRenderer;

	bool LeftTop = false;
	bool LeftBottom = false;
	bool RightTop = false;
	bool RightBottom = false;

	float Ratio = 0;
	float Line = 0;

	int Score = 0;
	int BrickHP = 0;
	EBrickType BrickType;
	//bool CollisionCheck = false;
	
	U2DCollision* CollisionComponent = nullptr;

	APlayer* Vaus = nullptr;
	ABall* ResultBall = nullptr;
	APlayerLife* PlayerLife = nullptr;

	FIntPoint TileCount;
	std::string SpriteName;
	FVector2D TileSize;
	std::vector<std::vector<Tile>> AllTiles;

};

