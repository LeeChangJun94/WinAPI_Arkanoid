#pragma once
#include <EngineCore/Actor.h>
#include <EnginePlatform/EngineSound.h>

class APlayer;
class ABall;
class ADeathLine;
class USpriteRenderer;
class ABoss;

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

	void SetLifeCount(int _LifeCount)
	{
		LifeCount += _LifeCount;
	}

	int GetLifeCount()
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

	void SetDeathLine(ADeathLine* _DeathLine)
	{
		DeathLine = _DeathLine;
	}
	
	void SetBoss(ABoss* _Boss)
	{
		Boss = _Boss;
	}

	std::list<ABall*> BallList;
	static int LifeCount;
	bool VausDestroy;

protected:

private:
	APlayer* Vaus = nullptr;
	ABall* Ball = nullptr;
	ADeathLine* DeathLine = nullptr;
	USpriteRenderer* SpriteRenderer = nullptr;
	ABoss* Boss = nullptr;

	//APlayerLife* PlayerLife = nullptr;

};

