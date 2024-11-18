#pragma once

// Ό³Έν :
class ABossStage
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

protected:

private:

};

