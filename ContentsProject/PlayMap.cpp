#include "PreCompile.h"
#include "PlayMap.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

APlayMap::APlayMap()
{
	SpriteRenderer1 = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer1->SetOrder(ERenderOrder::BACKGROUND);
	SpriteRenderer1->SetComponentScale({ 672, 720 });
	SpriteRenderer1->SetComponentLocation({ 336, 408 });

	USpriteRenderer* SpriteRenderer2 = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer2->SetOrder(ERenderOrder::BACKGROUND);
	SpriteRenderer2->SetSprite("UI_TOP.png");
	SpriteRenderer2->SetComponentScale({ 672, 48 });
	SpriteRenderer2->SetComponentLocation({ 336, 24 });
}

APlayMap::~APlayMap()
{
}

void APlayMap::BeginPlay()
{
	Super::BeginPlay();

	switch (PlayMapType)
	{
	case EPlayMapType::TYPE_1:
		SpriteRenderer1->SetSprite("BackGround_TYPE1.png");
		break;
	case EPlayMapType::TYPE_2:
		SpriteRenderer1->SetSprite("BackGround_TYPE2.png");
		break;
	case EPlayMapType::TYPE_3:
		SpriteRenderer1->SetSprite("BackGround_TYPE3.png");
		break;
	case EPlayMapType::TYPE_4:
		SpriteRenderer1->SetSprite("BackGround_TYPE4.png");
		break;
	case EPlayMapType::TYPE_BOSS:
		SpriteRenderer1->SetSprite("BackGround_Boss.png");
		break;
	case EPlayMapType::TYPE_DARK:
		SpriteRenderer1->SetSprite("Dark.png");
		break;
	case EPlayMapType::TYPE_INTRO:
		SpriteRenderer1->SetSprite("BackGround_Intro.png");
	default:
		break;
	}
}