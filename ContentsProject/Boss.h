#pragma once

// Ό³Έν :
class ABoss : public AActor
{
public:
	// constrcuter destructer
	ABoss();
	~ABoss();

	// delete Function
	ABoss(const ABoss& _Other) = delete;
	ABoss(ABoss&& _Other) noexcept = delete;
	ABoss& operator=(const ABoss& _Other) = delete;
	ABoss& operator=(ABoss&& _Other) noexcept = delete;

protected:

private:

};

