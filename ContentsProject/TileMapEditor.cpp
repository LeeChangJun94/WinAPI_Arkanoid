#include "PreCompile.h"
#include "TileMapEditor.h"
#include "Brick.h"
#include "PlayMap.h"
#include "GlobalValue.h"
#include "ContentsEnum.h"
#include "TitleGameMode.h"
#include <EngineCore/Level.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineRandom.h>


ATileMapEditor::ATileMapEditor()
{
	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentScale({ 10, 10 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::MousePoint);
	CollisionComponent->SetCollisionType(ECollisionType::CirCle);
}

ATileMapEditor::~ATileMapEditor()
{
}

// 타일찍고 저장할 수 있는 레벨
void ATileMapEditor::BeginPlay()
{
	Super::BeginPlay();

	APlayMap* PlayMap = GetWorld()->SpawnActor<APlayMap>();
	PlayMap->SetPlayMapType(EPlayMapType::TYPE_1);

	Bricks.resize(UGlobalValue::BrickY);

	for (int i = 0; i < UGlobalValue::BrickY; ++i)
	{
		Bricks[i].resize(UGlobalValue::BrickX);
	}

	for (int i = static_cast<int>(EBrickType::WHITE); i <= static_cast<int>(EBrickType::GOLD); ++i)
	{
		ABrick* SelectBricks = GetWorld()->SpawnActor<ABrick>();
		SelectBricks->SetActorLocation({ 120.0f + i * UGlobalValue::BrickSize.X, 600.0f });
		SelectBricks->SetBrickType(static_cast<EBrickType>(i));
	}
}

void ATileMapEditor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('T'))
	{
		UEngineAPICore::GetCore()->ResetLevel<ATitleGameMode, AActor>("Title");
		UEngineAPICore::GetCore()->OpenLevel("Title");
	}

	if (true == UEngineInput::GetInst().IsDown('S'))
	{
		CollisionComponent->SetComponentLocation(UEngineAPICore::GetCore()->GetMainWindow().GetMousePos());

		CurBrick = reinterpret_cast<ABrick*>(CollisionComponent->CollisionOnce(ECollisionGroup::Brick));

		if (nullptr != CurBrick)
		{
			CurBrickType = CurBrick->GetBrickType();
		}
	}

	if (true == UEngineInput::GetInst().IsPress(VK_LBUTTON))
	{
		FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

		MousePos -= UGlobalValue::StartBrickPos;

		FVector2D IndexPos = MousePos / UGlobalValue::BrickSize;

		FIntPoint TilePoint = IndexPos.ConvertToPoint();

		if (IndexOver(TilePoint))
		{
			return;
		}

		if (nullptr != Bricks[TilePoint.Y][TilePoint.X])
		{
			return;
		}

		FVector2D CreatePos;
		CreatePos.X = TilePoint.X * UGlobalValue::BrickSize.X;
		CreatePos.Y = TilePoint.Y * UGlobalValue::BrickSize.Y;
		CreatePos += UGlobalValue::StartBrickPos;

		ABrick* Print = GetWorld()->SpawnActor<ABrick>();
		Print->SetActorLocation(CreatePos + UGlobalValue::BrickSize.Half());
		Print->SetBrickType(CurBrickType);
		Bricks[TilePoint.Y][TilePoint.X] = Print;
	}

	if (true == UEngineInput::GetInst().IsPress(VK_RBUTTON))
	{
		FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

		MousePos -= UGlobalValue::StartBrickPos;

		FVector2D IndexPos = MousePos / UGlobalValue::BrickSize;

		FIntPoint TilePoint = IndexPos.ConvertToPoint();

		if (IndexOver(TilePoint))
		{
			return;
		}

		if (nullptr == Bricks[TilePoint.Y][TilePoint.X])
		{
			return;
		}

		if (nullptr != Bricks[TilePoint.Y][TilePoint.X])
		{
			Bricks[TilePoint.Y][TilePoint.X]->Destroy();
			Bricks[TilePoint.Y][TilePoint.X] = nullptr;
		}
	}

	if (true == UEngineInput::GetInst().IsPress('Q'))
	{
		ClearBrick();
	}

	if (true == UEngineInput::GetInst().IsPress('O'))
	{
		ClearBrick();

		UEngineDirectory Dir;

		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}

		Dir.Append("Data");

		UEngineWindow& Window = UEngineAPICore::GetCore()->GetMainWindow();

		OPENFILENAME OFN;
		char filePathName[100] = "";
		char lpstrFile[100] = "";
		static char filter[] = "*.BData";

		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = Window.GetWindowHandle();
		OFN.lpstrFilter = filter;
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 100;
		
		std::string Path = Dir.GetPathToString();
		OFN.lpstrInitialDir = Path.c_str();

		if (GetOpenFileNameA(&OFN) != 0)
		{
			std::string FilePath = OFN.lpstrFile;


			UEngineSerializer Ser;
			UEngineFile File = FilePath;
			File.FileOpen("rb");
			File.Read(Ser);

			std::vector<FVector2D> Positions;
			std::vector<int> Types;

			Ser >> Positions;
			Ser >> Types;

			for (size_t i = 0; i < Positions.size(); i++)
			{
				FVector2D IndexPos = (Positions[i] - UGlobalValue::StartBrickPos) / UGlobalValue::BrickSize;
				FIntPoint TilePoint = IndexPos.ConvertToPoint();

				FVector2D CreatePos;
				CreatePos.X = TilePoint.X * UGlobalValue::BrickSize.X;
				CreatePos.Y = TilePoint.Y * UGlobalValue::BrickSize.Y;
				CreatePos += UGlobalValue::StartBrickPos;

				ABrick* Print = GetWorld()->SpawnActor<ABrick>();
				Print->SetActorLocation(CreatePos + UGlobalValue::BrickSize.Half());
				Print->SetBrickType(static_cast<EBrickType>(Types[i]));
				Bricks[TilePoint.Y][TilePoint.X] = Print;
			}
		}
	}

	if (true == UEngineInput::GetInst().IsPress('P'))
	{
		UEngineDirectory Dir;

		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}

		Dir.Append("Data");


		UEngineWindow& Window = UEngineAPICore::GetCore()->GetMainWindow();

		OPENFILENAME OFN;
		char filePathName[100] = "";
		char lpstrFile[100] = "";

		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OFN);
		OFN.hwndOwner = Window.GetWindowHandle();
		OFN.lpstrFile = lpstrFile;
		OFN.lpstrFile[0] = '\0';
		OFN.nMaxFile = sizeof(lpstrFile);
		OFN.lpstrFilter = "Brick Data (*.BData)\0*.BData\0";
		OFN.nFilterIndex = 1;
		OFN.lpstrFileTitle = NULL;
		OFN.nMaxFileTitle = 0;
		OFN.lpstrInitialDir = NULL;
		// OFN.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_EXPLORER | OFN_ENABLEHOOK;

		std::string Path = Dir.GetPathToString();

		OFN.lpstrInitialDir = Path.c_str();



		if (GetSaveFileNameA(&OFN) != 0)
		{
			UEnginePath Path = lpstrFile;
			std::string Ext = Path.GetExtension();
			std::string UpperExt = UEngineString::ToUpper(Ext);
			if (UpperExt != ".BDATA")
			{
				std::string FileName = Path.GetFileName();
				FileName += ".BData";
				Path.MoveParent();
				Path.Append(FileName);
			}

			std::vector<FVector2D> Positions;
			std::vector<int> Types;

			for (size_t y = 0; y < Bricks.size(); y++)
			{
				for (size_t x = 0; x < Bricks[y].size(); x++)
				{
					if (nullptr != Bricks[y][x])
					{
						Positions.push_back(Bricks[y][x]->GetActorLocation());
						Types.push_back(static_cast<int>(Bricks[y][x]->GetBrickType()));
					}
				}
			}

			UEngineSerializer Ser;
			Ser << Positions;
			Ser << Types;

			UEngineFile File = Path.GetFileName();
			File.FileOpen("wb");
			File.Write(Ser);

		}
	}
}

bool ATileMapEditor::IndexOver(FIntPoint _TilePoint)
{
	if (0 > _TilePoint.X)
	{
		return true;
	}

	if (0 > _TilePoint.Y)
	{
		return true;
	}

	if (UGlobalValue::BrickX <= _TilePoint.X)
	{
		return true;
	}

	if (UGlobalValue::BrickY <= _TilePoint.Y)
	{
		return true;
	}

	return false;
}

void ATileMapEditor::ClearBrick()
{
	for (size_t y = 0; y < Bricks.size(); y++)
	{
		for (size_t x = 0; x < Bricks[y].size(); x++)
		{
			if (nullptr != Bricks[y][x])
			{
				Bricks[y][x]->Destroy();
				Bricks[y][x] = nullptr;
			}
		}
	}
}