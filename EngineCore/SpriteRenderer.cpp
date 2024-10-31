#include "PreCompile.h"
#include "SpriteRenderer.h"
#include "ImageManager.h"

USpriteRenderer::USpriteRenderer()
{
}

USpriteRenderer::~USpriteRenderer()
{
}

// SpriteRenderer : public URenderer
// MeshRenderer : public URenderer
// StaticMeshRenderer : public URenderer
void USpriteRenderer::Render()
{

}

void USpriteRenderer::BeginPlay()
{

}

void USpriteRenderer::ComponentTick(float _DeltaTime)
{

}

void USpriteRenderer::SetSprite(std::string_view _Name, int _CurIndex /*= 0*/)
{
	// �̱��濡 ���ؼ� �����Ҷ�
	// ���� ���ϰ� �����ϱ� ���ؼ� ����ϴ� �Ŷ�� �ϸ� Ʋ�ȴ�.
	// ��ü�� �� 1�� ����� �����̶�� ���� ���� ���ð�

	// ���Ͱ� ������������� �ε尡 ���� ��Ȳ�̾�� �Ѵ�.
	Sprite = UImageManager::GetInst().FindSprite(_Name);

	if (nullptr == Sprite)
	{
		MSGASSERT("�ε����� ���� ��������Ʈ�� ����Ϸ��� �߽��ϴ�" + std::string(_Name));
		return;
	}

	CurIndex = _CurIndex;
}
