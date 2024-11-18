#include "PreCompile.h"
#include "TileMapEditor.h"
//#include "SelectBrick.h"
#include "Brick.h"
#include "PlayMap.h"
#include "GlobalValue.h"
#include "ContentsEnum.h"
#include <EngineCore/Level.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineRandom.h>


ATileMapEditor::ATileMapEditor()
{
	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentScale({ 10, 10 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::MousePoint);
	CollisionComponent->SetCollisionType(ECollisionType::CirCle);
}

ATileMapEditor::~ATileMapEditor()
{
}

// 타일찍고 저장할 수 있는 레벨
void ATileMapEditor::BeginPlay()
{
	Super::BeginPlay();

	APlayMap* Stage1 = GetWorld()->SpawnActor<APlayMap>();

	Bricks.resize(UGlobalValue::BrickY);

	for (int i = 0; i < UGlobalValue::BrickY; ++i)
	{
		Bricks[i].resize(UGlobalValue::BrickX);
	}

	for (int i = static_cast<int>(EBrickType::WHITE); i <= static_cast<int>(EBrickType::GOLD); ++i)
	{
		ABrick* SelectBricks = GetWorld()->SpawnActor<ABrick>();
		SelectBricks->SetActorLocation({ 120.0f + i * UGlobalValue::BrickSize.X, 600.0f });
		SelectBricks->SetBrickType(static_cast<EBrickType>(i));
	}
}

void ATileMapEditor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	CollisionComponent->SetComponentLocation(UEngineAPICore::GetCore()->GetMainWindow().GetMousePos());

	CurBrick = reinterpret_cast<ABrick*>(CollisionComponent->CollisionOnce(ECollisionGroup::Brick));

	if (true == UEngineInput::GetInst().IsDown('S') && nullptr != CurBrick)
	{
		CurBrickType = CurBrick->GetBrickType();
	}

	if (true == UEngineInput::GetInst().IsPress(VK_LBUTTON))
	{
		FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

		MousePos -= UGlobalValue::StartBrickPos;

		FVector2D IndexPos = MousePos / UGlobalValue::BrickSize;

		FIntPoint TilePoint = IndexPos.ConvertToPoint();
		
		if (IndexOver(TilePoint))
		{
			return;
		}

		if (nullptr != Bricks[TilePoint.Y][TilePoint.X])
		{
			return;
		}
		
		FVector2D CreatePos;
		CreatePos.X = TilePoint.X * UGlobalValue::BrickSize.X;
		CreatePos.Y = TilePoint.Y * UGlobalValue::BrickSize.Y;
		CreatePos += UGlobalValue::StartBrickPos;

		ABrick* Print = GetWorld()->SpawnActor<ABrick>();
		Print->SetActorLocation(CreatePos + UGlobalValue::BrickSize.Half());
		Print->SetBrickType(CurBrickType);
		Bricks[TilePoint.Y][TilePoint.X] = Print;
	}
	
	if (true == UEngineInput::GetInst().IsPress(VK_RBUTTON))
	{
		FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

		MousePos -= UGlobalValue::StartBrickPos;

		FVector2D IndexPos = MousePos / UGlobalValue::BrickSize;

		FIntPoint TilePoint = IndexPos.ConvertToPoint();

		if (IndexOver(TilePoint))
		{
			return;
		}

		if (nullptr == Bricks[TilePoint.Y][TilePoint.X])
		{
			return;
		}

		if (nullptr != Bricks[TilePoint.Y][TilePoint.X])
		{
			Bricks[TilePoint.Y][TilePoint.X]->Destroy();
			Bricks[TilePoint.Y][TilePoint.X] = nullptr;
		}
	}


}

bool ATileMapEditor::IndexOver(FIntPoint _TilePoint)
{
	if (0 > _TilePoint.X)
	{
		return true;
	}
	
	if (0 > _TilePoint.Y)
	{
		return true;
	}

	if (UGlobalValue::BrickX <= _TilePoint.X)
	{
		return true;
	}

	if (UGlobalValue::BrickY <= _TilePoint.Y)
	{
		return true;
	}

	return false;
}