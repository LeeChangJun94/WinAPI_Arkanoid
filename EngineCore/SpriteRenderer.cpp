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
	// 싱글톤에 대해서 설명할때
	// 값을 편하게 공유하기 위해서 사용하는 거라고 하면 틀렸다.
	// 객체를 단 1개 만드는 패턴이라는 것을 잊지 마시고

	// 액터가 만들어졌을때는 로드가 끝난 상황이어야 한다.
	Sprite = UImageManager::GetInst().FindSprite(_Name);

	if (nullptr == Sprite)
	{
		MSGASSERT("로드하지 않은 스프라이트를 사용하려고 했습니다" + std::string(_Name));
		return;
	}

	CurIndex = _CurIndex;
}
