#include "PreCompile.h"
#include "PlayGameMode.h"
#include "Brick.h"

#include <EngineCore/Level.h>

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	ABrick* Ptr = GetWorld()->SpawnActor<ABrick>();
}