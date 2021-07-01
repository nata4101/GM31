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

void Game::Init()
{
	AddGameObject<CCamera>(CAMERA_OBJECT);

	AddGameObject<CField>(THREED_OBJECT);

	AddGameObject<CPlayer>(THREED_OBJECT);

	AddGameObject<CEnemy>(THREED_OBJECT)->SetPosition(D3DXVECTOR3(-3, 1, 5));

	AddGameObject<CEnemy>(THREED_OBJECT)->SetPosition(D3DXVECTOR3(0, 1, 5));

	AddGameObject<CEnemy>(THREED_OBJECT)->SetPosition(D3DXVECTOR3(3, 1, 5));

	//AddGameObject<CBullet>();

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
