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
	APlayMap* PMAP0 = GetWorld()->SpawnActor<APlayMap>();
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			ABrick* Ptr = GetWorld()->SpawnActor<ABrick>();
			Ptr->SetActorLocation({ 64 + (BrickScale.iX() * i), 160 + (BrickScale.iY() * j) });
			Ptr->SetActorScale({ BrickScale.iX(), BrickScale.iY() });
		}
	}
	//ABrick* Ptr = GetWorld()->SpawnActor<ABrick>();
}