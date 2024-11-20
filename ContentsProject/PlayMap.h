#pragma once
#include <EngineCore/Actor.h>

enum class EPlayMapType
{
	TYPE_4,
	TYPE_1,
	TYPE_2,
	TYPE_3,
	TYPE_BOSS,
	TYPE_DARK,
};

// Ό³Έν :
class APlayMap : public AActor
{
public:
	// constrcuter destructer
	APlayMap();
	~APlayMap();

	// delete Function
	APlayMap(const APlayMap& _Other) = delete;
	APlayMap(APlayMap&& _Other) noexcept = delete;
	APlayMap& operator=(const APlayMap& _Other) = delete;
	APlayMap& operator=(APlayMap&& _Other) noexcept = delete;

	void BeginPlay();

	void SetPlayMapType(EPlayMapType _PlayMapType)
	{
		PlayMapType = _PlayMapType;
	}

	//void PlayMapTYPE_1();
	//void PlayMapTYPE_2();
	//void PlayMapTYPE_3();
	//void PlayMapTYPE_4();
	//void PlayMapTYPE_Boss();





protected:

private:
	EPlayMapType PlayMapType = EPlayMapType::TYPE_DARK;
	USpriteRenderer* SpriteRenderer1 = nullptr;
};

