#include "Result.h"
#include "Title.h"
#include "sprite.h"
#include "input.h"
#include "manager.h"

void Result::Init()
{
	CSprite* sprite = AddGameObject<CSprite>(TWOD_OBJECT);
	sprite->SetResource("asset/texture/result.jpg");
	sprite->SetRotation(DXVector3(0, 0, 0));
	sprite->SetPosition(DXVector3(0, 0, 0));
	sprite->SetScale(DXVector3(SCREEN_WIDTH, SCREEN_HEIGHT, 1));
}

void Result::Update()
{
	CScene::Update();

	if (Input::GetKeyTrigger(VK_RETURN)) {
		Manager::GetInstance()->SetScene<Title>();
	}
}
