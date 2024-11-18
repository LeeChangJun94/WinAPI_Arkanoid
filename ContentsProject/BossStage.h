#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

class APlayer;

// Ό³Έν :
class ABossStage : public AGameMode
{
public:
	// constrcuter destructer
	ABossStage();
	~ABossStage();

	// delete Function
	ABossStage(const ABossStage& _Other) = delete;
	ABossStage(ABossStage&& _Other) noexcept = delete;
	ABossStage& operator=(const ABossStage& _Other) = delete;
	ABossStage& operator=(ABossStage&& _Other) noexcept = delete;

	void BeginPlay();

protected:

private:
	APlayer* Vaus = nullptr;
	USoundPlayer BGMPlayer;
};

