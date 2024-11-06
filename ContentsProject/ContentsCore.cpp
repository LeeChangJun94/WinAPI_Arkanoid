#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include <EngineBase/EngineDirectory.h>

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/ImageManager.h>

#include "TitleGameMode.h"
#include "PlayGameMode.h"
#include "TileMapGameMode.h"
#include "Player.h"


ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

// ������ ����ǰ� �� 1�� ����ȴ�.
void ContentsCore::BeginPlay()
{
	// UEngineDirectory Dir = "C:\\AAA";

	UEngineDirectory Dir;

	// ����ΰ� �߿��ϴ�.
	// ��� ����� �ٽ��� �̰��̴�.
	// ���� ��� ����ƴ����� �߿����� �ʾƾ� �Ѵ�.
	if (false == Dir.MoveParentToDirectory("Resources"))
	{
		MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
		return;
	}

	//Dir.Append("Image");

	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].GetPathToString();
		UImageManager::GetInst().Load(FilePath);
	}


	// �Ϲ� �ؽ�ó�� �� �ε��Ǹ�
	// �ڸ��� �۾��� �Ʒ��� ���ִ°� ����.
	{

		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("Resources");
		Dir.Append("Text");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());

	}
	//UImageManager::GetInst().CuttingSprite("Text.png", { 24, 24 });

	{
		UImageManager::GetInst().CuttingSprite("Fields2.png", { 224, 240 });
		UImageManager::GetInst().CuttingSprite("UI_TOP.png", { 672, 48 });
		UImageManager::GetInst().CuttingSprite("Title1.png", { 672, 768 });
		UImageManager::GetInst().CuttingSprite("Title2.png", { 672, 168 });
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
	}
	
	{
		UImageManager::GetInst().CuttingSprite("Ball.png", { 10, 8 });
		UImageManager::GetInst().CuttingSprite("Bullet.png", { 48, 72 });
		UImageManager::GetInst().CuttingSprite("Bricks1.png", { 48, 24 });
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
	//	// Ÿ�ϼ� �ε�
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

	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");

	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
	//UEngineAPICore::GetCore()->CreateLevel("End");
	//UEngineAPICore::GetCore()->CreateLevel<ATileMapGameMode, AActor>("Tile");

	UEngineAPICore::GetCore()->OpenLevel("Title");

	//UEngineAPICore::GetCore()->CreateLevel<ATileMapGameMode, AActor>("Tile");

	//UEngineAPICore::GetCore()->OpenLevel("Tile");

}

void ContentsCore::Tick()
{
	// ���� ���� �뵵�� ã�� ���ؼ� ������� �ʴ� �Լ��Դϴ�.
}