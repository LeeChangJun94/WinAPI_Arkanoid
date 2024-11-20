#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include <EngineBase/EngineDirectory.h>

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/ImageManager.h>
#include <EnginePlatform/EngineSound.h>

#include "TitleGameMode.h"
#include "Stage_001.h"
#include "stage_002.h"
#include "stage_003.h"
#include "stage_004.h"
#include "stage_005.h"
#include "stage_006.h"
#include "stage_007.h"
#include "stage_008.h"
#include "stage_009.h"
#include "stage_010.h"
#include "stage_011.h"
#include "stage_012.h"
#include "stage_013.h"
#include "stage_014.h"
#include "stage_015.h"
#include "stage_016.h"
#include "stage_017.h"
#include "stage_018.h"
#include "stage_019.h"
#include "stage_020.h"
#include "stage_021.h"
#include "stage_022.h"
#include "stage_023.h"
#include "stage_024.h"
#include "stage_025.h"
#include "stage_026.h"
#include "stage_027.h"
#include "stage_028.h"
#include "stage_029.h"
#include "stage_030.h"
#include "Stage_031.h"
#include "Stage_032.h"
#include "Stage_Boss.h"
#include "TileMapEditor.h"
#include "Player.h"


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
		Dir.Append("Image\\Text");

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
		UImageManager::GetInst().CuttingSprite("UI_TOP.png", { 672, 48 });
		UImageManager::GetInst().CuttingSprite("Title1.png", { 672, 768 });
		UImageManager::GetInst().CuttingSprite("Title2.png", { 672, 168 });
		UImageManager::GetInst().CuttingSprite("DethLine.png", { 672, 2 });
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
		UImageManager::GetInst().CuttingSprite("BossAttack.png", { 24, 24 });
		UImageManager::GetInst().CuttingSprite("Bricks.png", { 48, 24 });
		//UImageManager::GetInst().CuttingSprite("Bricks2.png", { 48, 24 });
		UImageManager::GetInst().CuttingSprite("Item1.png", { 32, 14 });
		UImageManager::GetInst().CuttingSprite("Item2.png", { 32, 14 });
	}

	//{
	//
	//	UEngineDirectory BombDir;
	//	BombDir.MoveParentToDirectory("Resources");
	//	BombDir.Append("bomb");
	//
	//	UImageManager::GetInst().LoadFolder(BombDir.GetPathToString());
	//
	//}

	//{
	//	// 타일셋 로드
	//	UEngineDirectory Dir;
	//	Dir.MoveParentToDirectory("Resources");
	//	Dir.Append("TileMap//TileSet");
	//
	//	UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
	//
	//}

	//UEngineDirectroy Dir;

	//Dir.SetPath("C:\\Resources");

	//std::vector<UEngineFile> AllFile = Dir.GetAllFile("*.Bmp", "*.Png");

	//for (size_t i = 0; i < AllFile.size(); i++)
	//{
	//	ImageManager::Load(AllFile[i].GetPath());
	//}




	//UEngineAPICore::GetCore()->CreateLevel("Title");
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("Arkanoid");

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 672, 768 });

	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");

	UEngineAPICore::GetCore()->CreateLevel<AStage_001, APlayer>("Stage_001");
	UEngineAPICore::GetCore()->CreateLevel<AStage_002, APlayer>("Stage_002");
	UEngineAPICore::GetCore()->CreateLevel<AStage_003, APlayer>("Stage_003");
	UEngineAPICore::GetCore()->CreateLevel<AStage_004, APlayer>("Stage_004");
	UEngineAPICore::GetCore()->CreateLevel<AStage_005, APlayer>("Stage_005");
	UEngineAPICore::GetCore()->CreateLevel<AStage_006, APlayer>("Stage_006");
	UEngineAPICore::GetCore()->CreateLevel<AStage_007, APlayer>("Stage_007");
	UEngineAPICore::GetCore()->CreateLevel<AStage_008, APlayer>("Stage_008");
	UEngineAPICore::GetCore()->CreateLevel<AStage_009, APlayer>("Stage_009");
	UEngineAPICore::GetCore()->CreateLevel<AStage_010, APlayer>("Stage_010");
	UEngineAPICore::GetCore()->CreateLevel<AStage_011, APlayer>("Stage_011");
	UEngineAPICore::GetCore()->CreateLevel<AStage_012, APlayer>("Stage_012");
	UEngineAPICore::GetCore()->CreateLevel<AStage_013, APlayer>("Stage_013");
	UEngineAPICore::GetCore()->CreateLevel<AStage_014, APlayer>("Stage_014");
	UEngineAPICore::GetCore()->CreateLevel<AStage_015, APlayer>("Stage_015");
	UEngineAPICore::GetCore()->CreateLevel<AStage_016, APlayer>("Stage_016");
	UEngineAPICore::GetCore()->CreateLevel<AStage_017, APlayer>("Stage_017");
	UEngineAPICore::GetCore()->CreateLevel<AStage_018, APlayer>("Stage_018");
	UEngineAPICore::GetCore()->CreateLevel<AStage_019, APlayer>("Stage_019");
	UEngineAPICore::GetCore()->CreateLevel<AStage_020, APlayer>("Stage_020");
	UEngineAPICore::GetCore()->CreateLevel<AStage_021, APlayer>("Stage_021");
	UEngineAPICore::GetCore()->CreateLevel<AStage_022, APlayer>("Stage_022");
	UEngineAPICore::GetCore()->CreateLevel<AStage_023, APlayer>("Stage_023");
	UEngineAPICore::GetCore()->CreateLevel<AStage_024, APlayer>("Stage_024");
	UEngineAPICore::GetCore()->CreateLevel<AStage_025, APlayer>("Stage_025");
	UEngineAPICore::GetCore()->CreateLevel<AStage_026, APlayer>("Stage_026");
	UEngineAPICore::GetCore()->CreateLevel<AStage_027, APlayer>("Stage_027");
	UEngineAPICore::GetCore()->CreateLevel<AStage_028, APlayer>("Stage_028");
	UEngineAPICore::GetCore()->CreateLevel<AStage_029, APlayer>("Stage_029");
	UEngineAPICore::GetCore()->CreateLevel<AStage_030, APlayer>("Stage_030");
	UEngineAPICore::GetCore()->CreateLevel<AStage_031, APlayer>("Stage_031");
	UEngineAPICore::GetCore()->CreateLevel<AStage_032, APlayer>("Stage_032");
	UEngineAPICore::GetCore()->CreateLevel<AStage_Boss, APlayer>("Stage_Boss");
	
	UEngineAPICore::GetCore()->CreateLevel<ATileMapEditor, AActor>("Tile");
	//UEngineAPICore::GetCore()->CreateLevel("End");
	
	UEngineAPICore::GetCore()->OpenLevel("Title");

	//UEngineAPICore::GetCore()->CreateLevel<ATileMapEditor, AActor>("Tile");

	//UEngineAPICore::GetCore()->OpenLevel("Tile");

}

void ContentsCore::Tick()
{
	// 지금 전혀 용도를 찾지 못해서 사용하지 않는 함수입니다.
}