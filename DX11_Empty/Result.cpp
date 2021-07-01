#include "Result.h"
#include "Title.h"
#include "sprite.h"
#include "input.h"
#include "manager.h"

void Result::Init()
{
	CSprite* sprite = AddGameObject<CSprite>(TWOD_OBJECT);
	sprite->SetResource("asset/texture/result.jpg");
	sprite->SetRotation(D3DXVECTOR3(0, 0, 0));
	sprite->SetPosition(D3DXVECTOR3(0, 0, 0));
	sprite->SetScale(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 1));
}

void Result::Update()
{
	CScene::Update();

	if (Input::GetKeyTrigger(VK_RETURN)) {
		Manager::GetInstance()->SetScene<Title>();
	}
}
