#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include "PlayGameMode.h"
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
	// MyWindow.Open();

	// �ƹ� ���� ���� �ڵ�.
	// �ִ� �Ե��� ��������Ѵ�.
	// TitleLevel = new ULevel();

	// ��ü�� �����ϴ� �Լ��� �������ִµ� �����ϸ� �ȵȴٴ°�.
	// �̰� ���ؼ� �ȸ��� �ֵ� => �� �ƹ��� ���� ���� ���ɼ��� ����.

	//UEngineAPICore::GetCore()->CreateLevel("Title");
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("Arkanoid");

	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	//UEngineAPICore::GetCore()->CreateLevel("End");

	UEngineAPICore::GetCore()->OpenLevel("Play");

}

void ContentsCore::Tick()
{
	// ���� ���� �뵵�� ã�� ���ؼ� ������� �ʴ� �Լ��Դϴ�.
}