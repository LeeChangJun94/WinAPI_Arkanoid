#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class APlayerLife : public AActor
{
public:
	
	static APlayerLife* PlayerLife;
	
	// constrcuter destructer
	APlayerLife();
	~APlayerLife();

	// delete Function
	APlayerLife(const APlayerLife& _Other) = delete;
	APlayerLife(APlayerLife&& _Other) noexcept = delete;
	APlayerLife& operator=(const APlayerLife& _Other) = delete;
	APlayerLife& operator=(APlayerLife&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	inline void SetLifeCount(int _LifeCount)
	{
		LifeCount += _LifeCount;
	}

	inline int GetLifeCount()
	{
		return LifeCount;
	}

	void LifeCheck();	
	bool DeathCheck();

	
	

protected:

private:
	int LifeCount = 2;

	class USpriteRenderer* SpriteRenderer;

};

