#pragma once
#include <EngineCore/Actor.h>


class ABall;
class USpriteRenderer;

// Ό³Έν :
class APlayerLife : public AActor
{
public:
		
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

	//inline void SetPlayerLife(APlayerLife* _PlayerLife)
	//{
	//	PlayerLife = _PlayerLife;
	//}

	void LifeCheck();	
	bool DeathCheck();

	void SetBall(ABall* _Ball)
	{
		Ball = _Ball;
	}
	
	std::list<ABall*> BallList;

protected:

private:
	int LifeCount = 2;

	ABall* Ball = nullptr;
	USpriteRenderer* SpriteRenderer = nullptr;

	//APlayerLife* PlayerLife = nullptr;

};

