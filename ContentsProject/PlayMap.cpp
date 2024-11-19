#include "PreCompile.h"
#include "PlayMap.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

APlayMap::APlayMap()
{
	USpriteRenderer* SpriteRenderer1 = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer1->SetOrder(ERenderOrder::BACKGROUND);
	SpriteRenderer1->SetSprite("BackGround_TYPE1.png");
	SpriteRenderer1->SetComponentScale({ 672, 720 });
	SpriteRenderer1->SetComponentLocation({ 336, 408 });

	/*SpriteRenderer1->CreateAnimation("BackGround_TYPE1", "BackGround_TYPE1.png", 0, 0, 0.0f, false);
	SpriteRenderer1->CreateAnimation("BackGround_TYPE2", "BackGround_TYPE2.png", 0, 0, 0.0f, false);
	SpriteRenderer1->CreateAnimation("BackGround_TYPE3", "BackGround_TYPE3.png", 0, 0, 0.0f, false);
	SpriteRenderer1->CreateAnimation("BackGround_TYPE4", "BackGround_TYPE4.png", 0, 0, 0.0f, false);
	SpriteRenderer1->CreateAnimation("BackGround_Boss", "BackGround_Boss.png", 0, 0, 0.0f, false);*/

	

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


	//switch (PlayMapType)
	//{
	//case EPlayMapType::TYPE_1:
	//	PlayMapTYPE_1();
	//	break;
	//case EPlayMapType::TYPE_2:
	//	PlayMapTYPE_2();
	//	break;
	//case EPlayMapType::TYPE_3:
	//	PlayMapTYPE_3();
	//	break;
	//case EPlayMapType::TYPE_4:
	//	PlayMapTYPE_4();
	//	break;
	//case EPlayMapType::TYPE_BOSS:
	//	PlayMapTYPE_Boss();
	//	break;
	//default:
	//	break;
	//}
}

//void APlayMap::PlayMapTYPE_1()
//{
//	SpriteRenderer1->ChangeAnimation("BackGround_TYPE1");
//}
//
//void APlayMap::PlayMapTYPE_2()
//{
//	SpriteRenderer1->ChangeAnimation("BackGround_TYPE2");
//}
//
//void APlayMap::PlayMapTYPE_3()
//{
//	SpriteRenderer1->ChangeAnimation("BackGround_TYPE3");
//}
//
//void APlayMap::PlayMapTYPE_4()
//{
//	SpriteRenderer1->ChangeAnimation("BackGround_TYPE4");
//}
//
//void APlayMap::PlayMapTYPE_Boss()
//{
//	SpriteRenderer1->ChangeAnimation("BackGround_Boss");
//}

