#include "PreCompile.h"
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>
#include "ContentsEnum.h"
#include "Brick.h"
#include "Player.h"
#include "Ball.h"
#include "Item.h"
#include "Score.h"


#include <EngineCore/ImageManager.h>
#include <EngineBase/EngineRandom.h>

//FVector2D ABrick::ReflectionVector[static_cast<int>(EReflectionDir::MAX)] = {
//	{1, 0},	// LEFT,
//	{-1, 0},	// RIGHT,
//	{0, 1},					// UP,
//	{0, -1},					// DOWN,
//};



ABrick::ABrick()
{
	//SetActorLocation({ 600, 300});
	//SetActorScale({ 32, 16 });

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Bricks.png");
	//SpriteRenderer->SetComponentScale({ 48, 24 });
	
	SpriteRenderer->CreateAnimation("White", "Bricks.png", 0, 0, 0.0f);
	SpriteRenderer->CreateAnimation("Orange", "Bricks.png", 1, 1, 0.0f);
	SpriteRenderer->CreateAnimation("Skyblue", "Bricks.png", 2, 2, 0.0f);
	SpriteRenderer->CreateAnimation("Green", "Bricks.png", 3, 3, 0.0f);
	SpriteRenderer->CreateAnimation("Red", "Bricks.png", 6, 6, 0.0f);
	SpriteRenderer->CreateAnimation("Blue", "Bricks.png", 7, 7, 0.0f);
	SpriteRenderer->CreateAnimation("Pink", "Bricks.png", 8, 8, 0.0f);
	SpriteRenderer->CreateAnimation("Yellow", "Bricks.png", 9, 9, 0.0f);
	SpriteRenderer->CreateAnimation("Silver", "Bricks.png", 12, 17, 0.2f);
	SpriteRenderer->CreateAnimation("Gold", "Bricks.png", 18, 23, 0.2f);

	//SpriteRenderer->ChangeAnimation("Silver");

	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 48, 24 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Brick);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);
} 

ABrick::~ABrick()
{
}


void ABrick::BeginPlay()
{
	Vaus = GetWorld()->GetPawn<APlayer>();

	switch (BrickType)
	{
	case EBrickType::WHITE:
		WhiteBrick();
		break;
	case EBrickType::ORANGE:
		OrangeBrick();
		break;
	case EBrickType::SKYBLUE:
		SkyBlueBrick();
		break;
	case EBrickType::GREEN:
		GreenBrick();
		break;
	case EBrickType::RED:
		RedBrick();
		break;
	case EBrickType::BLUE:
		BlueBrick();
		break;
	case EBrickType::PINK:
		PinkBrick();
		break;
	case EBrickType::YELLOW:
		YellowBrick();
		break;
	case EBrickType::SILVER:
		SilverBrick();
		break;
	case EBrickType::GOLD:
		GoldBrick();
		break;
	default:
		break;
	}
}

//bool ABrick::RectCheck()
//{
//	// �ʿ��� ������ �� ��Ƽ� �����Ѵ�.
//	FTransform BallTransform = ABall::Ball->GetTransform();
//	FTransform BrickTransform = SpriteRenderer->GetActorTransform();
//
//	FVector2D LeftTop = BrickTransform.CenterLeftTop();
//	FVector2D RatioPos = BallTransform.Location - LeftTop;
//
//	// ��갪���� �̸� ����� ���´�.
//	RatioPos.X /= 48;
//	RatioPos.Y /= 24;
//
//	// ���� �ƴ� ���׸����ϱ� �����Ѵ�.
//
//	if (0.0f > RatioPos.X)
//	{
//		return false;
//	}
//
//	if (0.0f > RatioPos.Y)
//	{
//		return false;
//	}
//
//	if (1.0f < RatioPos.X)
//	{
//		return false;
//	}
//
//	if (1.0f < RatioPos.Y)
//	{
//		return false;
//	}
//
//	return true;
//}

//bool ABrick::RectCheck()
//{
//	FTransform BallTransform = Ball->GetTransform();
//	FTransform BrickTransform = SpriteRenderer->GetActorTransform();
//
//	if (BallTransform.Location.X < BrickTransform.Location.X && BallTransform.Location.X > (BrickTransform.Location.X - (BrickTransform.Scale.X / 2)) &&
//		BallTransform.Location.Y > (BrickTransform.Location.Y - (BrickTransform.Scale.Y / 2)) && BallTransform.Location.Y < BrickTransform.Location.Y)
//	{
//		LeftTop = true;
//		return LeftTop;
//	}
//	
//	if (BallTransform.Location.X < BrickTransform.Location.X && BallTransform.Location.X >(BrickTransform.Location.X - (BrickTransform.Scale.X / 2)) &&
//		BallTransform.Location.Y < (BrickTransform.Location.Y + (BrickTransform.Scale.Y / 2)) && BallTransform.Location.Y > BrickTransform.Location.Y)
//	{
//		LeftBottom = true;
//		return LeftBottom;
//	}
//
//	if (BallTransform.Location.X > BrickTransform.Location.X && BallTransform.Location.X < (BrickTransform.Location.X + (BrickTransform.Scale.X / 2)) &&
//		BallTransform.Location.Y > (BrickTransform.Location.Y - (BrickTransform.Scale.Y / 2)) && BallTransform.Location.Y < BrickTransform.Location.Y)
//	{
//		RightTop = true;
//		return RightTop;
//	}
//
//	if (BallTransform.Location.X > BrickTransform.Location.X && BallTransform.Location.X < (BrickTransform.Location.X + (BrickTransform.Scale.X / 2)) &&
//		BallTransform.Location.Y < (BrickTransform.Location.Y + (BrickTransform.Scale.Y / 2)) && BallTransform.Location.Y > BrickTransform.Location.Y)
//	{
//		RightBottom = true;
//		return RightBottom;
//	}
//
//	LeftTop = false;
//	LeftBottom = false;
//	RightTop = false;
//	RightBottom = false;
//
//	return false;
//}

//EReflectionDir ABrick::ReflectionDirCheck()
//{
//	FTransform BallTransform = ABall::Ball->GetTransform();
//	FTransform BrickTransform = SpriteRenderer->GetActorTransform();
//
//	FVector2D LeftTop = BrickTransform.CenterLeftTop();
//	FVector2D LRRatioPos = BallTransform.Location - LeftTop;
//
//	// ��갪���� �̸� ����� ���´�.
//	LRRatioPos.X /= 48;
//	LRRatioPos.Y /= 24;
//
//	// ���� ������ ������ ���´�.
//	// ���࿡ ���� �Ʒ��� �ڵ带 �߸� ®�ٸ�
//	EReflectionDir Dir = EReflectionDir::MAX;
//
//	// ������ �ﰢ��
//	if (LRRatioPos.X > LRRatioPos.Y)
//	{
//		Dir = EReflectionDir::RIGHT;
//	}
//	else 
//	{
//		Dir = EReflectionDir::LEFT;
//	}
//
//	FVector2D BTRatioPos = LRRatioPos;
//	BTRatioPos.X = 1.0f - BTRatioPos.X;
//	BTRatioPos.Y = 1.0f - BTRatioPos.Y;
//
//	if (BTRatioPos.X < BTRatioPos.Y)
//	{
//		if (Dir == EReflectionDir::RIGHT)
//		{
//			Dir = EReflectionDir::UP;
//		}
//	}
//	else 
//	{
//		if (Dir == EReflectionDir::LEFT)
//		{
//			Dir = EReflectionDir::DOWN;
//		}
//	}
//
//	return Dir;
//}

//EReflectionDir ABrick::ReflectionDirCheck()
//{
//	FTransform BallTransform = //Ball->GetTransform();
//	FTransform BrickTransform = SpriteRenderer->GetActorTransform();
//
//	float Ratio = (BrickTransform.Scale.Y / 2) / (BrickTransform.Scale.X / 2);
//
//	float LeftLine = (-Ratio) * (BallTrans.Location.X - BrickTrans.Location.X);
//	float RightLine = Ratio * (BallTrans.Location.X - BrickTrans.Location.X);
//
//	EReflectionDir Dir = EReflectionDir::MAX;
//
//	if (true == LeftTop)
//	{
//		if (LeftLine > (BrickTrans.Location.Y - BallTrans.Location.Y))
//		{
//			Dir = EReflectionDir::LEFT;
//		}
//		else
//		{
//			Dir = EReflectionDir::UP;
//		}
//	}
//	
//	if (true == LeftBottom)
//	{
//		if (RightLine > (BrickTrans.Location.Y - BallTrans.Location.Y))
//		{
//			Dir = EReflectionDir::LEFT;
//		}
//		else
//		{
//			Dir = EReflectionDir::DOWN;
//		}
//	}
//
//	if (true == RightTop)
//	{
//		if (RightLine > (BrickTrans.Location.Y - BallTrans.Location.Y))
//		{
//			Dir = EReflectionDir::RIGHT;
//		}
//		else
//		{
//			Dir = EReflectionDir::UP;
//		}
//	}
//
//	if (true == RightBottom)
//	{
//		if (LeftLine < (BrickTrans.Location.Y - BallTrans.Location.Y))
//		{
//			Dir = EReflectionDir::RIGHT;
//		}
//		else
//		{
//			Dir = EReflectionDir::DOWN;
//		}
//	}
//
//	return Dir;
//}

void ABrick::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//if (true == RectCheck())
	//{
	//	EReflectionDir Dir = ReflectionDirCheck();
	//
	//	FVector2D DirVector = ReflectionVector[static_cast<int>(Dir)];
	//
	//	DirVector = ABall::Ball->Dir.Reflect(DirVector);
	//
	//	ABall::Ball->Dir = DirVector;
	//
	//	this->Destroy();
	//
	//}
	//
	//return;

	BrickTrans.Location = { GetActorLocation() };

	FVector2D BrickSize = SpriteRenderer->GetComponentScale();

	Ratio = (BrickSize.Y / 2) / (BrickSize.X / 2);

	ResultBall = reinterpret_cast<ABall*>(CollisionComponent->CollisionOnce(ECollisionGroup::Ball));

	if (nullptr != ResultBall)
	{
		BallTrans.Location = { ResultBall->GetActorLocation() };
		//Brick ����
		if (BallTrans.Location.X < BrickTrans.Location.X && BallTrans.Location.X >(BrickTrans.Location.X - (BrickSize.X / 2)) &&
			BallTrans.Location.Y > (BrickTrans.Location.Y - (BrickSize.Y / 2)) && BallTrans.Location.Y < BrickTrans.Location.Y)
		{
			Line = (-Ratio) * (BallTrans.Location.X - BrickTrans.Location.X);

			if ((Line) > (BrickTrans.Location.Y - BallTrans.Location.Y))
			{
				UEngineDebug::OutPutString("Left");
				if (ResultBall->GetBallDir().X > 0)
				{
					BallReflect();

					BrickDestroyCheck();
				}
			}
			else
			{
				UEngineDebug::OutPutString("Top");
				if (ResultBall->GetBallDir().Y > 0)
				{
					BallReflect();

					BrickDestroyCheck();
				}
			}
		}

		if (BallTrans.Location.X < BrickTrans.Location.X && BallTrans.Location.X >(BrickTrans.Location.X - (BrickSize.X / 2)) &&
			BallTrans.Location.Y < (BrickTrans.Location.Y + (BrickSize.Y / 2)) && BallTrans.Location.Y > BrickTrans.Location.Y)
		{
			Line = Ratio * (BallTrans.Location.X - BrickTrans.Location.X);

			if ((Line) < (BrickTrans.Location.Y - BallTrans.Location.Y))
			{
				UEngineDebug::OutPutString("Left");
				if (ResultBall->GetBallDir().X > 0)
				{
					BallReflect();

					BrickDestroyCheck();
				}
			}
			else
			{
				UEngineDebug::OutPutString("Bottom");
				if (ResultBall->GetBallDir().Y < 0)
				{
					BallReflect();

					BrickDestroyCheck();
				}
			}
		}


		//Brick ������
		if (BallTrans.Location.X > BrickTrans.Location.X && BallTrans.Location.X < (BrickTrans.Location.X + (BrickSize.X / 2)) &&
			BallTrans.Location.Y >(BrickTrans.Location.Y - (BrickSize.Y / 2)) && BallTrans.Location.Y < BrickTrans.Location.Y)
		{
			Line = Ratio * (BallTrans.Location.X - BrickTrans.Location.X);

			if ((Line) > (BrickTrans.Location.Y - BallTrans.Location.Y))
			{
				UEngineDebug::OutPutString("Right");
				if (ResultBall->GetBallDir().X < 0)
				{
					BallReflect();

					BrickDestroyCheck();
				}
			}
			else
			{
				UEngineDebug::OutPutString("Top");
				if (ResultBall->GetBallDir().Y > 0)
				{
					BallReflect();

					BrickDestroyCheck();
				}
			}
		}

		if (BallTrans.Location.X > BrickTrans.Location.X && BallTrans.Location.X < (BrickTrans.Location.X + (BrickSize.X / 2)) &&
			BallTrans.Location.Y < (BrickTrans.Location.Y + (BrickSize.Y / 2)) && BallTrans.Location.Y > BrickTrans.Location.Y)
		{
			Line = (-Ratio) * (BallTrans.Location.X - BrickTrans.Location.X);

			if ((Line) < (BrickTrans.Location.Y - BallTrans.Location.Y))
			{
				UEngineDebug::OutPutString("Right");
				if (ResultBall->GetBallDir().X < 0)
				{
					BallReflect();

					BrickDestroyCheck();
				}
			}
			else
			{
				UEngineDebug::OutPutString("Bottom");
				if (ResultBall->GetBallDir().Y < 0)
				{
					BallReflect();

					BrickDestroyCheck();
				}
			}
		}
	}
}

void ABrick::BrickDestroyCheck()
{
	BrickHP -= 1;

	if (0 == BrickHP)
	{
		this->Destroy();

		AItem* Ptr = GetWorld()->SpawnActor<AItem>();
		Ptr->SetActorLocation(GetActorLocation());
		Ptr->SetPlayerLife(PlayerLife);
		Ptr->SetBall(ResultBall);

		Vaus->AddPlayerScore(Score);
	}
}

void ABrick::BallReflect()
{
	FVector2D Dir;
	Dir = ResultBall->GetBallDir().Reflect(FVector2D::DOWN);

	ResultBall->SetBallDir(Dir);
}

void ABrick::WhiteBrick()
{
	SpriteRenderer->ChangeAnimation("White");
	Score = 50;
	BrickHP = 1;
}

void ABrick::OrangeBrick()
{
	SpriteRenderer->ChangeAnimation("Orange");
	Score = 60;
	BrickHP = 1;
}

void ABrick::SkyBlueBrick()
{
	SpriteRenderer->ChangeAnimation("SkyBlue");
	Score = 70;
	BrickHP = 1;
}

void ABrick::GreenBrick()
{
	SpriteRenderer->ChangeAnimation("Green");
	Score = 80;
	BrickHP = 1;
}

void ABrick::RedBrick()
{
	SpriteRenderer->ChangeAnimation("Red");
	Score = 90;
	BrickHP = 1;
}

void ABrick::BlueBrick()
{
	SpriteRenderer->ChangeAnimation("Blue");
	Score = 100;
	BrickHP = 1;
}

void ABrick::PinkBrick()
{
	SpriteRenderer->ChangeAnimation("Pink");
	Score = 110;
	BrickHP = 1;
}

void ABrick::YellowBrick()
{
	SpriteRenderer->ChangeAnimation("Yellow");
	Score = 120;
	BrickHP = 1;
}

void ABrick::SilverBrick()
{
	SpriteRenderer->ChangeAnimation("Silver");
	Score = 50;
	BrickHP = 2;
}

void ABrick::GoldBrick()
{
	SpriteRenderer->ChangeAnimation("Gold");
	Score = 0;
	BrickHP = -1;
}




void ABrick::Create(std::string_view _Sprite, FIntPoint _Count, FVector2D _TileSize)
{
	SpriteName = _Sprite;
	TileSize = _TileSize;
	TileCount = _Count;

	AllTiles.resize(_Count.Y);

	for (size_t y = 0; y < AllTiles.size(); y++)
	{
		AllTiles[y].resize(_Count.X);;
	}

	// Ÿ�ϸ��� �ٽ� 0, 0�� �ΰ����� ���ؾ� �Ѵ�.
	// Ÿ�Ϸμ��� 0,0�� ����.
	// Ÿ���� ��ġ�� ����μ��� Ÿ�ϸ� * �ε����� �ȴ�.


}

FVector2D ABrick::IndexToTileLocation(FIntPoint _Index)
{
	return FVector2D(24 + _Index.X * TileSize.X, 72 + _Index.Y * TileSize.Y);
}

FIntPoint ABrick::LocationToIndex(FVector2D _Location)
{
	FVector2D Location = _Location / TileSize;

	return FIntPoint( Location.iX(),Location.iY());
}

// ���콺 ��ġ�� �÷��̾� ��ġ�� ��������.
void ABrick::SetTileLocation(FVector2D _Location, int _SpriteIndex)
{
	FVector2D TilePos = _Location - FVector2D(24, 72);//- GetActorLocation();

	FIntPoint Point = LocationToIndex(TilePos);

	if (true == IsIndexOver(Point))
	{
		return;
	}

	SetTileIndex(Point, _SpriteIndex);
}

bool ABrick::IsIndexOver(FIntPoint _Index)
{
	if (0 > _Index.X)
	{
		return true;
	}

	if (0 > _Index.Y)
	{
		return true;
	}

	if (TileCount.X - 1 < _Index.X)
	{
		return true;
	}

	if (TileCount.Y - 1 < _Index.Y)
	{
		return true;
	}

	return false;
}

void ABrick::SetTileIndex(FIntPoint _Index, int _SpriteIndex)
{
	SetTileIndex(_Index, { 0,0 }, TileSize, _SpriteIndex);
}

void ABrick::SetTileIndex(FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, int _SpriteIndex)
{
	if (true == IsIndexOver(_Index))
	{
		return;
	}

	// �̸� �� ������ �ʰ�
	// ���� 

	// SPriteRenderer�� ����.
	// �����ȸ�������ٴ� �̾߱�
	// �������� ��������Ʈ �������� �����.

	// �����ڿ��� �ۿ� ������ٸ�.
	// �������� �����ϴ°� ���Ѵٰ� ����.

	// �������ڸ��� Ÿ���� �� ��� ���°� �������� ����� �ִ�.
	if (nullptr == AllTiles[_Index.Y][_Index.X].SpriteRenderer)
	{
		USpriteRenderer* NewSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		// AllTiles[TileCount.Y][TileCount.X].SpriteRenderer;
		NewSpriteRenderer->SetComponentScale(TileSize);
		AllTiles[_Index.Y][_Index.X].SpriteRenderer = NewSpriteRenderer;
	}

	// ��������Ʈ�� ������ �����Ƿ�.
	// �� �̸����� �������ָ� �ȴ�.

	USpriteRenderer* FindSprite = AllTiles[_Index.Y][_Index.X].SpriteRenderer;
	FindSprite->SetSprite(SpriteName, _SpriteIndex);

	FVector2D TileLocation = IndexToTileLocation(_Index);
	FindSprite->SetComponentScale(_SpriteScale);
	// �Ʒ��ʿ� �������� �������� ���߿� �ȴ�.
	FindSprite->SetOrder(_Index.Y);

	AllTiles[_Index.Y][_Index.X].SpriteRenderer->SetComponentLocation(TileLocation + TileSize.Half() + _Pivot);
	AllTiles[_Index.Y][_Index.X].Pivot = _Pivot;
	AllTiles[_Index.Y][_Index.X].Scale = _SpriteScale;
	AllTiles[_Index.Y][_Index.X].SpriteIndex = _SpriteIndex;
}



Tile* ABrick::GetTileRef(FVector2D _Location)
{
	FIntPoint Point = LocationToIndex(_Location - FVector2D(24, 72));

	return GetTileRef(Point);
}

// Ÿ���� ���� ���� �̰ɷ� ���ͼ� ������Ű�� �ȴ�.
Tile* ABrick::GetTileRef(FIntPoint _Index)
{
	if (true == IsIndexOver(_Index))
	{
		return nullptr;
	}

	return &AllTiles[_Index.Y][_Index.X];
}

void ABrick::Serialize(UEngineSerializer& _Ser)
{
	// AllTiles

	// �����ϰ� �ʹ�.
	// : public ISerializObject ���
	// void Serialize(UEngineSerializer& _Ser)
	// void DeSerialize(UEngineSerializer & _Ser)
	// ����
	// �߿䵥���� �����ϴ� �ڵ� ���� ¥��

	_Ser << TileCount;
	_Ser << TileSize;
	_Ser << SpriteName;
	_Ser << AllTiles;
}

void ABrick::DeSerialize(UEngineSerializer& _Ser)
{
	// ������ �ִ��� �� ���������� �ε��ؾ� �Ѵ�.
	// ����

	// ��ø��� ������� ������ �����̾�� �մϴ�.
	// ���� �ٲٸ� ����� �ȵǰų�
	_Ser >> TileCount;
	_Ser >> TileSize;
	_Ser >> SpriteName;

	std::vector<std::vector<Tile>> LoadTiles;
	_Ser >> LoadTiles;

	// �����͸� �о����������.
	Create(SpriteName, TileCount, TileSize);

	for (int y = 0; y < LoadTiles.size(); y++)
	{
		for (int x = 0; x < LoadTiles[y].size(); x++)
		{
			SetTileIndex({ x, y }, LoadTiles[y][x].Pivot, LoadTiles[y][x].Scale, LoadTiles[y][x].SpriteIndex);
		}
	}

}
