#include "PreCompile.h"
#include "PlayMap.h"
#include <EngineCore/EngineAPICore.h>

APlayMap::APlayMap()
{
	// �Ź� ������ ����� �ٲ��
	// �̰� ��ü�� ��� ������ �ƴմϴ�.
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	SetActorLocation(WindowSize.Half());
	SetActorScale(WindowSize);
	
	SetSprite("Fields2.png");
}

APlayMap::~APlayMap()
{
}

