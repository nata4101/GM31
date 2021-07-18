#include "Game.h"
#include "polygon2D.h"
#include "Field.h"
#include "Camera.h"
#include "Enemy.h"
#include "Player.h"
#include "CBulet.h"
#include "Explosion.h"
#include "input.h"
#include "Result.h"
#include "manager.h"
#include "audio.h"

Audio* bgm;

void Game::Init()
{
	AddGameObject<CCamera>(CAMERA_OBJECT);

	AddGameObject<CField>(THREED_OBJECT);

	AddGameObject<CPlayer>(THREED_OBJECT);

	AddGameObject<CEnemy>(THREED_OBJECT)->SetPosition(XMFLOAT3(-3, 1, 5));
													
	AddGameObject<CEnemy>(THREED_OBJECT)->SetPosition(XMFLOAT3(0, 1, 5));
												
	AddGameObject<CEnemy>(THREED_OBJECT)->SetPosition(XMFLOAT3(3, 1, 5));

	//AddGameObject<CBullet>();

	bgm = new Audio;

	bgm->Init();

	bgm->Load("asset/sound/bgm_cyber44.wav");

	bgm->Play(true);

	AddGameObject<CPolygon2D>(TWOD_OBJECT);
	//AddGameObject<CExplosion>(THREED_OBJECT);
}

void Game::Update()
{
	CScene::Update();

	if (Input::GetKeyTrigger(VK_RETURN)) {
		Manager::GetInstance()->SetScene<Result>();
	}
}

void Game::Uninit()
{
	CScene::Uninit();
	bgm->Uninit();
	delete bgm;
}
