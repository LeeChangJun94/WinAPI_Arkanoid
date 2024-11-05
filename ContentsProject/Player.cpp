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


	// 랜더러를 하나 만든다.
	// 언리얼에서는 생서에서 CreateDefaultSubObject <= 생성자에서밖에 못합니다.
	// 무조건 만들어야 한다.
	// 다른데서하면 무조건 터져요.
	// 한번 생성자에서 만든 지울수도 없어.

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

	// 부모의 크기에 영향 안받게 만들것이다.



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


	// 직접 카메라 피봇을 설정해줘야 한다.
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
// 고생하기
//void APlayer::MoveFunction(FVector2D _Dir/*, AMonster* Monster*/)
//{
//	// 몬스터를 찾아오는 함수가 존재할것이다.
//	// 액터 전체르 관리하기 때문에.
//	// 찾아오는 함수가 존재합니다.
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
	//	// 하이퍼 FSM이라고 합니다
	//	// FSM의 변종입니다.
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

	//// 안누르고 있을때 
	//if (true == EngineInput::GetFree("PlayerMove"))

	//// 키를 땟을때
	//if (true == EngineInput::GetUp("PlayerMove"))

	//// 계속 누르는 도중
	//if (true == EngineInput::GetPress("PlayerMove"))

	//// 가장 처음 한번 눌렀을때
	//if (true == EngineInput::GetDown("PlayerMove"))

	// Time::DeltaTime;

	// 여러분들의 컴퓨터가 1프레임이고
	// 선생님의 컴퓨터가 2프레임이

	// 게임시작하고 얼마지났다?

	//         여러분  제컴퓨터는
	// 0.5초             0.5        =+> 0.5         // 0.0, 0.0, => 0.5, 0.0
	// 1.0초    1.0f     0.5        =+> 1.0         // 0.5, 0.0, => 1.0, 0.0
	// 1.5초             0.5        =+> 1.5 - 1.0
	// 2.0초    1.0f     0.5        =+> 1.0         // 1.0, 0.0, => 2.0, 0.0

	// 델타임


	// 엔진에서 
	// 0.0, 0.0, => 1.0, 0.0

	// 내가 정해줘야 한다.
	// 렉걸렸어
	// 컴퓨터의 성능과 상관없이 => 같은 게임 내용을 보여주기 위해서 입니다. 

	// 기본적으로 어떤 기능을 만들때는

	// 내가 게임 엔진을 하고 있다면 무조건 엔진이 제공하는 기능을 써야한다.
	// 구현할수 있는 능력이 있다고 해도 엔진의 기능을 사용해야 한다.
	// 1. 컨텐츠 많이 사용하고 있다.
	// 2. 그리고 엔진이 버전업 되면 내가 만든게 그냥 무너진다. 
	// <= 엔진 버전 올라가면 내가 만든 것이 무너질수 있다. 5.4
	//    엔진을 고칠때 말하는 것.

	// 내가 직접 만들어야 한다면
	// 1. OS냐 std냐를 따져야 합니다.
	// 2. OS 기본적으로 하드웨어에 관련된건 대부분 Window
	//    CPU도 포함 대표적으로 추후 쓰레드를 배울때 이해하게 됩니다.
	// 3. std는 보통 문법적 측면에서 접근하는 문제들이 std가 지원해줄 가능성이 높다.
	//    배열 => 배열이 불편해 => std::vector

	// 그러면 그걸 유저들에게 대표적인 방법 랩핑 
	// EngineWindow가 우리엔진의 대표적인 랩핑 클래스입니다.
	// WindowAPI의 기능을 절대로 그냥 공개하는 경우는 없다.

	// 윈도우가 제공하는 기본 입력함수입니다.
	// 입력버퍼는 윈도우가 알아서 처리해주기 때문에
	// 입력이 있을때만 0이 아닌 수를 리턴하는 함수입니다.

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

	// 마우스 왼쪽 버튼입니다.
	// 눌린 한순간만 체크할수 있는 기능이 필요하다.
	//if (3.0f < UEngineInput::GetInst().IsPreeTime(VK_LBUTTON))
	//{
	//	// 콘솔에서 슈팅 못만들면 API와서도 못만들어요.
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
//	// 아이들이라는 상태는 가만히 있는 상태이다.
//
//	// 전이에 대한 판단은 해야 합니다.
//	// 각스테이트에서 쳐야할 코드는
//	// 1. 전이조건
//
//
//	if (true == UEngineInput::GetInst().IsPress('A') ||
//		true == UEngineInput::GetInst().IsPress('D') ||
//		true == UEngineInput::GetInst().IsPress('W') ||
//		true == UEngineInput::GetInst().IsPress('S'))
//	{
//		// 상태를 바꾸는 순간은 그 바로 종료하는게 좋다.
//		// 최종적으로 상태를 바꿨다면 종료해라.
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