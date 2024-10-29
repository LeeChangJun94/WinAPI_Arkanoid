#include "PreCompile.h"
#include "PlayGameMode.h"

#include <EngineCore/Level.h>
#include "PlayMap.h"
#include "Brick.h"

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	//APlayMap* PMAP0 = GetWorld()->SpawnActor<APlayMap>();
	ABrick* Ptr = GetWorld()->SpawnActor<ABrick>();
}