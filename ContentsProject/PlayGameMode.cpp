#include "PreCompile.h"
#include "PlayGameMode.h"

#include <EngineCore/Level.h>
#include "PlayMap.h"
#include "Brick.h"
#include "Ball.h"

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	{
		APlayMap* NewActor = GetWorld()->SpawnActor<APlayMap>();
	}
	ABall* BallActor = GetWorld()->SpawnActor<ABall>();

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			ABrick* Ptr = GetWorld()->SpawnActor<ABrick>();
			Ptr->SetActorLocation({ 64 + (Ptr->GetActorScale().X * i), 160 + (Ptr->GetActorScale().Y * j) });
			Ptr->SetActorScale({ Ptr->GetActorScale().X, Ptr->GetActorScale().Y });
		}
	}
	//ABrick* Ptr = GetWorld()->SpawnActor<ABrick>();

}