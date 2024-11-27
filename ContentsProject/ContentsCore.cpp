#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include <EngineBase/EngineDirectory.h>

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/ImageManager.h>
#include <EnginePlatform/EngineSound.h>

#include "TitleGameMode.h"
#include "Stage.h"
#include "Stage_Dark.h"
#include "Stage_Boss.h"
#include "TileMapEditor.h"
#include "Player.h"
#include "Intro.h"
#include "Outtro.h"
#include "GameOver.h"


ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

// 엔진이 실행되고 단 1번 실행된다.
void ContentsCore::BeginPlay()
{
	{
		UEngineDirectory Dir;

		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}

		Dir.Append("Image");

		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UImageManager::GetInst().Load(FilePath);
		}

	}

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Sound");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineSound::Load(FilePath);
		}
	}

	{
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("Resources");
		Dir.Append("Image\\Score");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
	}
	
	{
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("Resources");
		Dir.Append("Image\\Text_Red");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
	}

	{
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("Resources");
		Dir.Append("Image\\Text_White");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
	}

	{
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("Resources");
		Dir.Append("Image\\Text_Yellow");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
	}

	{
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("Resources");
		Dir.Append("Image\\Number");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
	}

	{
		UImageManager::GetInst().CuttingSprite("BackGround_TYPE1.png", { 672, 720 });
		UImageManager::GetInst().CuttingSprite("BackGround_TYPE2.png", { 672, 720 });
		UImageManager::GetInst().CuttingSprite("BackGround_TYPE3.png", { 672, 720 });
		UImageManager::GetInst().CuttingSprite("BackGround_TYPE4.png", { 672, 720 });
		UImageManager::GetInst().CuttingSprite("BackGround_Boss.png", { 672, 720 });
		UImageManager::GetInst().CuttingSprite("BackGround_Space.png", { 672, 720 });
		UImageManager::GetInst().CuttingSprite("Dark.png", { 672, 720 });
		UImageManager::GetInst().CuttingSprite("UI_TOP.png", { 672, 48 });
		UImageManager::GetInst().CuttingSprite("Title1.png", { 672, 768 });
		UImageManager::GetInst().CuttingSprite("Title2.png", { 672, 168 });
		UImageManager::GetInst().CuttingSprite("DethLine.png", { 672, 2 });
	}
	
	{
		UImageManager::GetInst().CuttingSprite("InOuttro_Laser.png", { 384, 288 });
		UImageManager::GetInst().CuttingSprite("InOuttro_LaserEffect.png", { 128, 96 });
		UImageManager::GetInst().CuttingSprite("StarShip.png", { 573, 249 });
		UImageManager::GetInst().CuttingSprite("InOuttro_Enemies.png", { 64, 64 });
		UImageManager::GetInst().CuttingSprite("Intro_Vaus.png", { 33, 11 });
		UImageManager::GetInst().CuttingSprite("Outtro_Vaus.png", { 64, 16 });
	}

	{
		UImageManager::GetInst().CuttingSprite("Vaus_Idle.png", { 96, 24 });
		UImageManager::GetInst().CuttingSprite("Vaus_TEnlarge.png", { 144, 24 });
		UImageManager::GetInst().CuttingSprite("Vaus_Enlarge.png", { 144, 24 });
		UImageManager::GetInst().CuttingSprite("Vaus_TLaser.png", { 96, 24 });
		UImageManager::GetInst().CuttingSprite("Vaus_Laser.png", { 96, 24 });
		UImageManager::GetInst().CuttingSprite("Vaus_Destroy1.png", { 96, 24 });
		UImageManager::GetInst().CuttingSprite("Vaus_Destroy2.png", { 144, 72 });
		UImageManager::GetInst().CuttingSprite("Vaus_Create.png", { 96, 24 });

		UImageManager::GetInst().CuttingSprite("PlayerLife_0.png", { 240, 24 });
		UImageManager::GetInst().CuttingSprite("PlayerLife_1.png", { 240, 24 });
		UImageManager::GetInst().CuttingSprite("PlayerLife_2.png", { 240, 24 });
		UImageManager::GetInst().CuttingSprite("PlayerLife_3.png", { 240, 24 });
		UImageManager::GetInst().CuttingSprite("PlayerLife_4.png", { 240, 24 });
		UImageManager::GetInst().CuttingSprite("PlayerLife_5.png", { 240, 24 });
	}
	
	{
		UImageManager::GetInst().CuttingSprite("Ball.png", { 10, 8 });
		UImageManager::GetInst().CuttingSprite("Bullet.png", { 48, 24 });
		UImageManager::GetInst().CuttingSprite("Bricks.png", { 48, 24 });
		UImageManager::GetInst().CuttingSprite("Item1.png", { 32, 14 });
		UImageManager::GetInst().CuttingSprite("Item2.png", { 32, 14 });
	}

	{
		UImageManager::GetInst().CuttingSprite("Enemies_Type1.png", { 48, 48 });
		UImageManager::GetInst().CuttingSprite("Enemies_Type2.png", { 48, 48 });
		UImageManager::GetInst().CuttingSprite("Enemies_Type3.png", { 48, 48 });
		UImageManager::GetInst().CuttingSprite("Enemies_Type4.png", { 48, 48 });
		UImageManager::GetInst().CuttingSprite("Enemies_Destroy.png", { 48, 48 });
		UImageManager::GetInst().CuttingSprite("Boss.png", { 192, 288 });
		UImageManager::GetInst().CuttingSprite("Boss_Brick.png", { 144, 280 });
		UImageManager::GetInst().CuttingSprite("BossBullet.png", { 24, 24 });
	}
	
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("Arkanoid");

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 672, 768 });

	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
	UEngineAPICore::GetCore()->CreateLevel<AIntro, AActor>("Intro");
	UEngineAPICore::GetCore()->CreateLevel<AStage, APlayer>("Stage");
	UEngineAPICore::GetCore()->CreateLevel<AStage_Dark, APlayer>("Stage_Dark");
	UEngineAPICore::GetCore()->CreateLevel<AStage_Boss, APlayer>("Stage_Boss");
	UEngineAPICore::GetCore()->CreateLevel<AOuttro, APlayer>("Outtro");
	UEngineAPICore::GetCore()->CreateLevel<AGameOver, APlayer>("GameOver");
	UEngineAPICore::GetCore()->CreateLevel<ATileMapEditor, AActor>("Tile");

	UEngineAPICore::GetCore()->OpenLevel("GameOver");
}

void ContentsCore::Tick()
{
	// 지금 전혀 용도를 찾지 못해서 사용하지 않는 함수입니다.
}