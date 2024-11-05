#include "PreCompile.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>

#include <EnginePlatform/EngineInput.h>

#include <EnginePlatform/EngineWindow.h>
#include "Bullet.h"

APlayer* APlayer::Vaus = nullptr;

void APlayer::RunSoundPlay()
{
	//UEngineDebug::OutPutString("SoundPlay");
}

APlayer::APlayer()
{
	Vaus = this;

	//SetActorLocation({300, 700});

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Vaus.png");
	SpriteRenderer->SetComponentScale({ 144, 24 });
	SetActorLocation({ 300,900 });
	//SetActorScale(SpriteRenderer->GetComponentScale());

	SpriteRenderer->CreateAnimation("Idle", "Vaus.png", 0, 5, 0.1f);
	SpriteRenderer->ChangeAnimation("Idle");


	// �������� �ϳ� �����.
	// �𸮾󿡼��� �������� CreateDefaultSubObject <= �����ڿ����ۿ� ���մϴ�.
	// ������ ������ �Ѵ�.
	// �ٸ������ϸ� ������ ������.
	// �ѹ� �����ڿ��� ���� ������� ����.

	//{
	//	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//	SpriteRenderer->SetSprite("Player_Right.png");
	//	SpriteRenderer->SetComponentScale({ 300, 300 });
	//
	//	// SpriteRenderer->CreateAnimation("bomb", 0, 2, 0.1f);
	//
	//	SpriteRenderer->CreateAnimation("Run_Right", "Player_Right.png", 2, 4, 0.1f);
	//	SpriteRenderer->CreateAnimation("Idle_Right", "Player_Right.png", 0, 0, 0.1f);
	//
	//	SpriteRenderer->ChangeAnimation("Idle_Right");
	//
	//	// SpriteRenderer->CreateAnimation("Test", "Player_Right.png", { 5,  4,  3}, 0.1f);
	//	SpriteRenderer->SetAnimationEvent("Run_Right", 2, std::bind(&APlayer::RunSoundPlay, this));
	//}


	//{
	//	USpriteRenderer* Renderer = CreateDefaultSubObject<USpriteRenderer>();
	//	Renderer->SetSprite("Player_Right.png");
	//	Renderer->SetComponentLocation({ -100, 0 });
	//	Renderer->SetComponentScale({ 50, 50 });
	//}

	//{
	//	USpriteRenderer* Renderer = CreateDefaultSubObject<USpriteRenderer>();
	//	Renderer->SetSprite("Player_Right.png");
	//	Renderer->SetComponentLocation({ 100, 0 });
	//	Renderer->SetComponentScale({ 50, 50 });
	//}

	//{
	//	USpriteRenderer* Renderer = CreateDefaultSubObject<USpriteRenderer>();
	//	Renderer->SetSprite("Player_Right.png");
	//	Renderer->SetComponentLocation({ 0, -100 });
	//	Renderer->SetComponentScale({ 50, 50 });
	//}

	//{
	//	USpriteRenderer* Renderer = CreateDefaultSubObject<USpriteRenderer>();
	//	Renderer->SetSprite("Player_Right.png");
	//	Renderer->SetComponentLocation({ 0, 100 });
	//	Renderer->SetComponentScale({ 50, 50 });
	//}

	// �θ��� ũ�⿡ ���� �ȹް� ������̴�.



	//CreateDefaultSubObject<U2DCollision>();
}

APlayer::~APlayer()
{
}


void APlayer::BeginPlay()
{

	//Super::BeginPlay();
	//
	//Dir.Radian(30.f);
	//Dir.Normalize();


	// ���� ī�޶� �Ǻ��� ��������� �Ѵ�.
	//FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	//GetWorld()->SetCameraPivot(Size.Half() * -1.0f);
}

//	ChangeState(PlayerState::Idle);
//}
//
//void APlayer::IdleStart()
//{
//	SpriteRenderer->ChangeAnimation("Idle_Right");
//}
//
//void APlayer::ChangeState(PlayerState _CurPlayerState)
//{
//	switch (_CurPlayerState)
//	{
//	case PlayerState::Idle:
//		IdleStart();
//		break;
//	case PlayerState::Move:
//		MoveStart();
//		break;
//	case PlayerState::Jump:
//		break;
//	default:
//		break;
//	}
//
//	CurPlayerState = _CurPlayerState;
//
//}

// class LeftPlayer
// class RightPlayer
// ����ϱ�
//void APlayer::MoveFunction(FVector2D _Dir/*, AMonster* Monster*/)
//{
//	// ���͸� ã�ƿ��� �Լ��� �����Ұ��̴�.
//	// ���� ��ü�� �����ϱ� ������.
//	// ã�ƿ��� �Լ��� �����մϴ�.
//
//	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
//
//	AddActorLocation(_Dir * DeltaTime * Speed);
//}

//void APlayer::LeftMove()
//{
//	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
//
//	AddActorLocation(FVector2D::LEFT * DeltaTime * Speed);
//}

//void APlayer::RightMove()
//{
//	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
//
//	AddActorLocation(FVector2D::RIGHT * DeltaTime * Speed);
//}

//void APlayer::UpMove()
//{
//	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
//
//	AddActorLocation(FVector2D::UP * DeltaTime * Speed);
//}

//void APlayer::DownMove()
//{
//	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
//
//	AddActorLocation(FVector2D::DOWN * DeltaTime * Speed);
//}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));

	UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Title");
		//UEngineDebug::SwitchIsDebug();
	}

	BallTrans.Location = { ABall::Ball->GetActorLocation().iX(), ABall::Ball->GetActorLocation().iY() };
	//BallTrans.Scale = { ABall::Ball->GetActorScale().iX(), ABall::Ball->GetActorScale().iY() };
	
	//BallX = APlayer::Ball->GetActorLocation().iX();
	//BallY = APlayer::Ball->GetActorLocation().iY();
	//BallScaleX = APlayer::Ball->GetActorScale().iX();
	//BallScaleY = APlayer::Ball->GetActorScale().iY();
	
	FVector2D VausSize = SpriteRenderer->GetComponentScale();
	VausTrans.Location = { GetActorLocation().iX(), GetActorLocation().iY() };
	//VausSize = { GetActorScale().iX(), GetActorScale().iY() };
	
	//BrickX = GetActorLocation().iX();
	//BrickY = GetActorLocation().iY();
	//BrickScaleX = GetActorScale().iX();
	//BrickScaleY = GetActorScale().iY();
	
	Ratio = (VausSize.Y / 2) / (VausSize.X / 2);
	//line = ratio * (BallTrans.Location.X / 2) - (BrickSize.Y / 2);
	
	
	

	if (BallTrans.Location.X < VausTrans.Location.X && BallTrans.Location.X >(VausTrans.Location.X - (VausSize.X / 2)) &&
		BallTrans.Location.Y > (VausTrans.Location.Y - (VausSize.Y / 2)) && BallTrans.Location.Y < VausTrans.Location.Y)
	{
		Line = (-Ratio) * (BallTrans.Location.X - VausTrans.Location.X);
	
		if ((Line) > (VausTrans.Location.Y - BallTrans.Location.Y))
		{
			UEngineDebug::OutPutString("Left");
			if (ABall::Ball->Dir.X > 0)
			{
				FVector2D Dir;
				Dir = ABall::Ball->Dir.Reflect(FVector2D::LEFT);
	
				ABall::Ball->Dir = Dir;
	
				//APlayer::Ball->Dir.X *= -1;
			}
		}
		else
		{
			UEngineDebug::OutPutString("Top");
			if (ABall::Ball->Dir.Y > 0)
			{
				if (BallTrans.Location.X > VausTrans.Location.X - ((VausSize.X / 2) * 0.2))
				{
					FVector2D Dir;
					Dir.Radian(-30.0f);//ABall::Ball->Dir.Reflect(FVector2D::UP);

					ABall::Ball->Dir = Dir;
				}
				else if (BallTrans.Location.X > VausTrans.Location.X - ((VausSize.X / 2) * 0.6))
				{
					FVector2D Dir;
					Dir.Radian(-45.0f);

					ABall::Ball->Dir = Dir;
				}
				else
				{
					FVector2D Dir;
					Dir.Radian(-60.0f);

					ABall::Ball->Dir = Dir;
				}

	
				//ABall::Ball->Dir.Y *= -1;
			}
	
		}
	}
	
	if (BallTrans.Location.X < VausTrans.Location.X && BallTrans.Location.X >(VausTrans.Location.X - (VausSize.X / 2)) &&
		BallTrans.Location.Y < (VausTrans.Location.Y + (VausSize.Y / 2)) && BallTrans.Location.Y > VausTrans.Location.Y)
	{
		Line = Ratio * (BallTrans.Location.X - VausTrans.Location.X);
	
		if ((Line) < (VausTrans.Location.Y - BallTrans.Location.Y))
		{
			UEngineDebug::OutPutString("Left");
			if (ABall::Ball->Dir.X > 0)
			{
				FVector2D Dir;
				Dir = ABall::Ball->Dir.Reflect(FVector2D::LEFT);
	
				ABall::Ball->Dir = Dir;
	
				//ABall::Ball->Dir.X *= -1;
			}
		}
		else
		{
			UEngineDebug::OutPutString("Bottom");
			if (ABall::Ball->Dir.Y < 0)
			{
				FVector2D Dir;
				Dir = ABall::Ball->Dir.Reflect(FVector2D::DOWN);
	
				ABall::Ball->Dir = Dir;
	
				//APlayer::Ball->Dir.Y *= -1;
			}
		}
	}
	
	

	if (BallTrans.Location.X > VausTrans.Location.X && BallTrans.Location.X < (VausTrans.Location.X + (VausSize.X / 2)) &&
		BallTrans.Location.Y >(VausTrans.Location.Y - (VausSize.Y / 2)) && BallTrans.Location.Y < VausTrans.Location.Y)
	{
		Line = Ratio * (BallTrans.Location.X - VausTrans.Location.X);
	
		if ((Line) > (VausTrans.Location.Y - BallTrans.Location.Y))
		{
			UEngineDebug::OutPutString("Right");
			if (ABall::Ball->Dir.X < 0)
			{
				FVector2D Dir;
				Dir = ABall::Ball->Dir.Reflect(FVector2D::RIGHT);
	
				ABall::Ball->Dir = Dir;
	
				//ABall::Ball->Dir.X *= -1;
			}
		}
		else
		{
			UEngineDebug::OutPutString("Top");
			if (ABall::Ball->Dir.Y > 0)
			{
				if (BallTrans.Location.X < VausTrans.Location.X + ((VausSize.X / 2) * 0.2))
				{
					FVector2D Dir;
					Dir.Radian(30.0f);//ABall::Ball->Dir.Reflect(FVector2D::UP);

					ABall::Ball->Dir = Dir;
				}
				else if (BallTrans.Location.X < VausTrans.Location.X + ((VausSize.X / 2) * 0.6))
				{
					FVector2D Dir;
					Dir.Radian(45.0f);

					ABall::Ball->Dir = Dir;
				}
				else
				{
					FVector2D Dir;
					Dir.Radian(60.0f);

					ABall::Ball->Dir = Dir;
				}
			}
		}
	}
	
	if (BallTrans.Location.X > VausTrans.Location.X && BallTrans.Location.X < (VausTrans.Location.X + (VausSize.X / 2)) &&
		BallTrans.Location.Y < (VausTrans.Location.Y + (VausSize.Y / 2)) && BallTrans.Location.Y > VausTrans.Location.Y)
	{
		Line = (-Ratio) * (BallTrans.Location.X - VausTrans.Location.X);
	
		if ((Line) < (VausTrans.Location.Y - BallTrans.Location.Y))
		{
			UEngineDebug::OutPutString("Right");
			if (ABall::Ball->Dir.X < 0)
			{
				FVector2D Dir;
				Dir = ABall::Ball->Dir.Reflect(FVector2D::RIGHT);
	
				ABall::Ball->Dir = Dir;
	
				//ABall::Ball->Dir.X *= -1;
			}
		}
		else
		{
			UEngineDebug::OutPutString("Bottom");
			if (ABall::Ball->Dir.Y < 0)
			{
				FVector2D Dir;
				Dir = ABall::Ball->Dir.Reflect(FVector2D::DOWN);
	
				ABall::Ball->Dir = Dir;
	
				//ABall::Ball->Dir.Y *= -1;
			}
		}
	}

	//switch (CurPlayerState)
	//{
	//case PlayerState::Idle:
	//	Idle(_DeltaTime);
	//	break;
	//case PlayerState::Move:
	//	Move(_DeltaTime);
	//	break;
	//case PlayerState::Jump:
	//	// ������ FSM�̶�� �մϴ�
	//	// FSM�� �����Դϴ�.
	//	break;
	//default:
	//	break;
	//}

	//AddActorLocation(Dir * _DeltaTime * Speed);
	
	//FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	//
	//if (32 > GetActorLocation().X)
	//{
	//	if (Dir.X < 0)
	//	{
	//		Dir = Dir.Reflect(FVector2D::RIGHT);
	//	}
	//}
	//
	//if (WindowSize.X - 32 < GetActorLocation().X)
	//{
	//	if (Dir.X > 0)
	//	{
	//		Dir = Dir.Reflect(FVector2D::LEFT);
	//	}
	//}
	//
	//if (32 > GetActorLocation().Y)
	//{
	//	if (Dir.Y < 0)
	//	{
	//		Dir = Dir.Reflect(FVector2D::DOWN);
	//	}
	//
	//}
	//
	//if (WindowSize.Y < GetActorLocation().Y)
	//{
	//	if (Dir.Y > 0)
	//	{
	//		Dir = Dir.Reflect(FVector2D::UP);
	//	}
	//}
	
	 
	//if (UEngineInput::GetInst().IsDown('A'))
	//{
	//	int a = 0;
	//}

	// EngineInput::GetFree(EngineKey::HOME)
	// if (true == EngineInput::GetFree('A'))

	//// �ȴ����� ������ 
	//if (true == EngineInput::GetFree("PlayerMove"))

	//// Ű�� ������
	//if (true == EngineInput::GetUp("PlayerMove"))

	//// ��� ������ ����
	//if (true == EngineInput::GetPress("PlayerMove"))

	//// ���� ó�� �ѹ� ��������
	//if (true == EngineInput::GetDown("PlayerMove"))

	// Time::DeltaTime;

	// �����е��� ��ǻ�Ͱ� 1�������̰�
	// �������� ��ǻ�Ͱ� 2��������

	// ���ӽ����ϰ� ��������?

	//         ������  ����ǻ�ʹ�
	// 0.5��             0.5        =+> 0.5         // 0.0, 0.0, => 0.5, 0.0
	// 1.0��    1.0f     0.5        =+> 1.0         // 0.5, 0.0, => 1.0, 0.0
	// 1.5��             0.5        =+> 1.5 - 1.0
	// 2.0��    1.0f     0.5        =+> 1.0         // 1.0, 0.0, => 2.0, 0.0

	// ��Ÿ��


	// �������� 
	// 0.0, 0.0, => 1.0, 0.0

	// ���� ������� �Ѵ�.
	// ���ɷȾ�
	// ��ǻ���� ���ɰ� ������� => ���� ���� ������ �����ֱ� ���ؼ� �Դϴ�. 

	// �⺻������ � ����� ���鶧��

	// ���� ���� ������ �ϰ� �ִٸ� ������ ������ �����ϴ� ����� ����Ѵ�.
	// �����Ҽ� �ִ� �ɷ��� �ִٰ� �ص� ������ ����� ����ؾ� �Ѵ�.
	// 1. ������ ���� ����ϰ� �ִ�.
	// 2. �׸��� ������ ������ �Ǹ� ���� ����� �׳� ��������. 
	// <= ���� ���� �ö󰡸� ���� ���� ���� �������� �ִ�. 5.4
	//    ������ ��ĥ�� ���ϴ� ��.

	// ���� ���� ������ �Ѵٸ�
	// 1. OS�� std�ĸ� ������ �մϴ�.
	// 2. OS �⺻������ �ϵ��� ���õȰ� ��κ� Window
	//    CPU�� ���� ��ǥ������ ���� �����带 ��ﶧ �����ϰ� �˴ϴ�.
	// 3. std�� ���� ������ ���鿡�� �����ϴ� �������� std�� �������� ���ɼ��� ����.
	//    �迭 => �迭�� ������ => std::vector

	// �׷��� �װ� �����鿡�� ��ǥ���� ��� ���� 
	// EngineWindow�� �츮������ ��ǥ���� ���� Ŭ�����Դϴ�.
	// WindowAPI�� ����� ����� �׳� �����ϴ� ���� ����.

	// �����찡 �����ϴ� �⺻ �Է��Լ��Դϴ�.
	// �Է¹��۴� �����찡 �˾Ƽ� ó�����ֱ� ������
	// �Է��� �������� 0�� �ƴ� ���� �����ϴ� �Լ��Դϴ�.

	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		//SpriteRenderer->ChangeAnimation("Run_Right");
		if (WindowSize.X - 32 > GetActorLocation().X + VausSize.Half().X)
		{
			AddActorLocation(FVector2D::RIGHT * _DeltaTime * (Speed * 2));
		}
	}
	if (true == UEngineInput::GetInst().IsPress('A'))
	{
		if (32 < GetActorLocation().X - VausSize.Half().X)
		{
			//SpriteRenderer->ChangeAnimation("Run_Right");
			AddActorLocation(FVector2D::LEFT * _DeltaTime * (Speed * 2));
		}
	}
	//if (true == UEngineInput::GetInst().IsPress('S'))
	//{
	//	//SpriteRenderer->ChangeAnimation("Run_Right");
	//	AddActorLocation(FVector2D::DOWN * _DeltaTime * (Speed * 2));
	//}
	//if (true == UEngineInput::GetInst().IsPress('W'))
	//{
	//	//SpriteRenderer->ChangeAnimation("Run_Right");
	//	AddActorLocation(FVector2D::UP * _DeltaTime * (Speed * 2));
	//}

	//if (true == UEngineInput::GetInst().IsDown('R'))
	//{
	//	SpriteRenderer->SetSprite("Ball.png", MySpriteIndex);
	//	++MySpriteIndex;
	//}

	// ���콺 ���� ��ư�Դϴ�.
	// ���� �Ѽ����� üũ�Ҽ� �ִ� ����� �ʿ��ϴ�.
	//if (3.0f < UEngineInput::GetInst().IsPreeTime(VK_LBUTTON))
	//{
	//	// �ֿܼ��� ���� ������� API�ͼ��� ��������.
	//	ABullet* Ptr = GetWorld()->SpawnActor<ABullet>();
	//	Ptr->SetActorLocation(GetActorLocation());
	//}

	// FVector2D PrevTransform != GetTransform();
	//if (true == UEngineInput::GetInst().IsDown('R'))
	//{
	//	SpriteRenderer->SetOrder(-2000);
	//}
	//else if(true == UEngineInput::GetInst().IsUp('R'))
	//{
	//	SpriteRenderer->SetOrder(2000);
	//}
	//if (false == UEngineInput::GetInst().IsPress('A') &&
	//	false == UEngineInput::GetInst().IsPress('D') &&
	//	false == UEngineInput::GetInst().IsPress('W') &&
	//	false == UEngineInput::GetInst().IsPress('S'))
	//{
	//	SpriteRenderer->ChangeAnimation("Idle_Right");
	//}

}

void APlayer::LevelChangeStart()
{
	Super::LevelChangeStart();
}

void APlayer::LevelChangeEnd()
{
	Super::LevelChangeEnd();


}

//void APlayer::Idle(float _DeltaTime)
//{
//	Gravity();
//
//
//	SpriteRenderer->ChangeAnimation("Idle_Right");
//
//	// ���̵��̶�� ���´� ������ �ִ� �����̴�.
//
//	// ���̿� ���� �Ǵ��� �ؾ� �մϴ�.
//	// ��������Ʈ���� �ľ��� �ڵ��
//	// 1. ��������
//
//
//	if (true == UEngineInput::GetInst().IsPress('A') ||
//		true == UEngineInput::GetInst().IsPress('D') ||
//		true == UEngineInput::GetInst().IsPress('W') ||
//		true == UEngineInput::GetInst().IsPress('S'))
//	{
//		// ���¸� �ٲٴ� ������ �� �ٷ� �����ϴ°� ����.
//		// ���������� ���¸� �ٲ�ٸ� �����ض�.
//		ChangeState(PlayerState::Move);
//		return;
//	}
//
//	if (true == UEngineInput::GetInst().IsPress(VK_SPACE))
//	{
//		ChangeState(PlayerState::Jump);
//		return;
//	}
//
//}