#include "PreCompile.h"
#include "Stage_Dark.h"

#include <EngineCore/Level.h>
#include "PlayMap.h"
#include "Player.h"
#include "ContentsEnum.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>

AStage_Dark::AStage_Dark()
{
}

AStage_Dark::~AStage_Dark()
{
}

void AStage_Dark::BeginPlay()
{
	Super::BeginPlay();

	APlayMap* Map = GetWorld()->SpawnActor<APlayMap>();
	Map->SetPlayMapType(EPlayMapType::TYPE_DARK);
}

void AStage_Dark::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UEngineAPICore::GetCore()->OpenLevel("Stage");
}