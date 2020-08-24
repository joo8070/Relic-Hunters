#include "stdafx.h"
#include "stageManager.h"
#include "player.h"

HRESULT stageManager::init()
{
	_eClickAnim = new animation;
	_eClickAnim->init(IMAGEMANAGER->findImage("eButton")->getWidth(), IMAGEMANAGER->findImage("eButton")->getHeight(),
		IMAGEMANAGER->findImage("eButton")->getFrameWidth(), IMAGEMANAGER->findImage("eButton")->getFrameHeight());
	_eClickAnim->setDefPlayFrame(false, false);
	_eClickAnim->setFPS(1);

	_itemManager = new itemManager;
	_itemManager->init();
	// ========== 임시변수 ========== //

	setShip();
	setShop();
	setEnemyStage();
	setBossStage();


	SCENEMANAGER->changeScene(_typeName[(int)stageType::STAGE_SHIP]);
	_nowStageName = _typeName[(int)stageType::STAGE_SHIP];
	CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 6280 - WINSIZEX, 2056 - WINSIZEY);

	//SCENEMANAGER->changeScene("intro");

	// ========== 임시변수 ========== //
	return S_OK;
}

void stageManager::render()
{
	SCENEMANAGER->render();

	if (_eClickAnim->isPlay())
	{
		CAMERAMANAGER->aniRender(getMemDC(), IMAGEMANAGER->findImage("eButton"), _player->getPlayerPos().x, (*_player->getPlayerRect()).top - 100, _eClickAnim, false);
		_eClickAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 6);
	}

}

void stageManager::update()
{
	if (_nowStageName == "STAGE_1_1")
	{
		_stage1_1->findPlayer(_nowStageName, _player->getPlayerPos());
		stage1_1Collsion();
	}

	else if (_nowStageName == "STAGE_BOSS")
	{
		_bossStage->update(_nowStageName, _player->getPlayerPos());
		stageBossCollision();
	}

	stageShipCollsion();

	stageShopCollsion();

	_itemManager->setNowStageName(_nowStageName);

	SCENEMANAGER->update();

}

void stageManager::release()
{

}

void stageManager::gotoShip()
{
	SCENEMANAGER->changeScene(_typeName[(int)stageType::STAGE_SHIP]);
	_player->spawnPos(_spawnPoint[(int)stageType::STAGE_SHIP]);
	_nowStageName = _typeName[(int)stageType::STAGE_SHIP];
	CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 6280 - WINSIZEX, 2056 - WINSIZEY);
}



void stageManager::setShip()
{
	_ship = new stageShip;
	_ship->init(_typeName[(int)stageType::STAGE_SHIP], _spawnPoint[(int)stageType::STAGE_SHIP], _itemManager);
	SCENEMANAGER->addScene(_typeName[(int)stageType::STAGE_SHIP], _ship);
}

void stageManager::setShop()
{
	_shop = new stageShop;
	_shop->init(_typeName[(int)stageType::STAGE_SHOP], _spawnPoint[(int)stageType::STAGE_SHOP], _itemManager);
	SCENEMANAGER->addScene(_typeName[(int)stageType::STAGE_SHOP], _shop);
}

void stageManager::setEnemyStage()
{
	_stage1_1 = new stage1_1;
	_stage1_1->init(_typeName[(int)stageType::STAGE_1_1], _spawnPoint[(int)stageType::STAGE_1_1], _itemManager);
	SCENEMANAGER->addScene(_typeName[(int)stageType::STAGE_1_1], _stage1_1);
}

void stageManager::setBossStage()
{
	_bossStage = new stageBoss;
	_bossStage->init(_typeName[(int)stageType::STAGE_BOSS], _spawnPoint[(int)stageType::STAGE_BOSS], _itemManager);
	SCENEMANAGER->addScene(_typeName[(int)stageType::STAGE_BOSS], _bossStage);
}

void stageManager::stageShipCollsion()
{
	if (_nowStageName != "STAGE_SHIP") return;

	objectManager* _om = _ship->getObjectManager();

	for (int i = 0; i < _om->getVStageShipObject().size(); i++)
	{
		// --------------------- 박스 충돌 --------------------- //
		if (_om->getVStageShipObject()[i]->getIsRemoveObject())
		{
			_om->removeShipObject(i);
			break;
		}


		if ((_om->getVStageShipObject()[i]->getcanObjectColiision()) == BOX)
		{
			if (isCollisionReaction(_om->getVStageShipObject()[i]->getObjectRect(), *_player->getPlayerRect()))
			{
				_player->refreshCenter();
				break;
			}


			for (int j = 0; j < _player->getBullet()->getVBullet().size(); j++)
			{
				if (isCollision(_om->getVStageShipObject()[i]->getObjectRect(), (*_player->getBullet()->getVBullet()[j]).rc))
				{
					_player->getBullet()->removeBullet(j);
					_om->getVStageShipObject()[i]->setDamage(_om->getVStageShipObject()[i]->getDamage() + 1);
					break;
				}

			}

		}
		// --------------------- 박스 충돌 --------------------- //


		// --------------------- 텔레포트 충돌 --------------------- //
		if ((_om->getVStageShipObject()[i]->getcanObjectColiision()) == TELEPORT)
		{
			if (isCollision(_om->getVStageShipObject()[i]->getObjectRect(), *_player->getPlayerRect()))
			{
				if (!_eClickAnim->isPlay())
					_eClickAnim->start();

				if (_om->getVStageShipObject()[i]->getTeleportStageNumber() == 1)// 1-1 Stage
				{

					if (KEYMANAGER->isOnceKeyDown('E'))
					{
						SCENEMANAGER->changeScene(_typeName[(int)stageType::STAGE_1_1]);
						_player->spawnPos(_spawnPoint[(int)stageType::STAGE_1_1]);
						_nowStageName = _typeName[(int)stageType::STAGE_1_1];
						CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 6280 - WINSIZEX, 2056 - WINSIZEY);
						_stage1_1->getAnim()->start();
						break;
					}
				}

				if (_om->getVStageShipObject()[i]->getTeleportStageNumber() == 2) // Boss Stage
				{
					if (KEYMANAGER->isOnceKeyDown('E'))
					{
						SCENEMANAGER->changeScene(_typeName[(int)stageType::STAGE_BOSS]);
						_player->spawnPos(_spawnPoint[(int)stageType::STAGE_BOSS]);
						_nowStageName = _typeName[(int)stageType::STAGE_BOSS];
						CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 5000 - WINSIZEX, 2733 - WINSIZEY);
						_bossStage->getAnim()->start();
						break;
					}
				}
				if (_om->getVStageShipObject()[i]->getTeleportStageNumber() == 3) // shop Stage
				{
					if (KEYMANAGER->isOnceKeyDown('E'))
					{
						SCENEMANAGER->changeScene(_typeName[(int)stageType::STAGE_SHOP]);
						_player->spawnPos(_spawnPoint[(int)stageType::STAGE_SHOP]);
						_nowStageName = _typeName[(int)stageType::STAGE_SHOP];
						CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 3000 - WINSIZEX, 1080 - WINSIZEY);
						_shop->getAnim()->start();
						break;
					}
				}
			}
		}
		// --------------------- 텔레포트 충돌 --------------------- //



	}

}

void stageManager::stage1_1Collsion()
{
	if (_nowStageName != "STAGE_1_1") return;

	objectManager* _om = _stage1_1->getSetObjectManager();
	MYPOINT tp;
	tp.x = 5000;
	tp.y = 1000;
	if (_stage1_1->getSetEnemyManager()->getVEnemy().size() <= 0 && !_isCreated)
	{
		_om->setStage1_1Teleport(tp);
		_isCreated = true;
	}


	for (int i = 0; i < _om->getVStage1_1Object().size(); i++)
	{
		if (_om->getVStage1_1Object()[i]->getIsRemoveObject())
		{
			_om->removeStage1_1Object(i);
			break;
		}

		if ((_om->getVStage1_1Object()[i]->getcanObjectColiision()) == HOLO)
		{
			if (isCollision(_om->getVStage1_1Object()[i]->getObjectRect(), *_player->getPlayerRect()))
			{
				if (!_eClickAnim->isPlay())
					_eClickAnim->start();

			}
		}




		// --------------------- 박스 & player 충돌 --------------------- //
		if ((_om->getVStage1_1Object()[i]->getcanObjectColiision()) == BOX)
		{
			if (isCollisionReaction(_om->getVStage1_1Object()[i]->getObjectRect(), *_player->getPlayerRect()))
			{
				_player->refreshCenter();
				break;
			}
			// --------------------- 박스 & player 충돌 --------------------- //

			// --------------------- 박스 & enemy 충돌 --------------------- //

			for (int j = 0; j < _stage1_1->getSetEnemyManager()->getVEnemy().size(); j++)
			{
				if (isCollision(_stage1_1->getSetEnemyManager()->getVEnemy()[j]->getEnemyRect(), _om->getVStage1_1Object()[i]->getObjectRect()))
				{
					_stage1_1->getSetEnemyManager()->getVEnemy()[j]->setIsBlock(true);
					break;
				}
			}

			// --------------------- 박스 & enemy 충돌 --------------------- //

			for (int j = 0; j < _player->getBullet()->getVBullet().size(); j++)
			{
				if (isCollision(_om->getVStage1_1Object()[i]->getObjectRect(), (*_player->getBullet()->getVBullet()[j]).rc))
				{

					_player->getBullet()->removeBullet(j);
					_om->getVStage1_1Object()[i]->setDamage(_om->getVStage1_1Object()[i]->getDamage() + 1);
					break;
				}

			}


		}
		// --------------------- 텔레포트 충돌 --------------------- //
		if ((_om->getVStage1_1Object()[i]->getcanObjectColiision()) == TELEPORT)
		{
			if (isCollision(_om->getVStage1_1Object()[i]->getObjectRect(), *_player->getPlayerRect()))
			{
				if (_om->getVStage1_1Object()[i]->getTeleportStageNumber() == 999)// 1-1 Stage
				{
					if (KEYMANAGER->isOnceKeyDown('E'))
					{
						SCENEMANAGER->changeScene(_typeName[(int)stageType::STAGE_SHIP]);
						_player->spawnPos(_spawnPoint[(int)stageType::STAGE_SHIP]);
						_nowStageName = _typeName[(int)stageType::STAGE_SHIP];
						CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 5500 - WINSIZEX, 2000 - WINSIZEY);
					}
				}
			}

		}
		// --------------------- 텔레포트 충돌 --------------------- //



	} //for (int i = 0; i < _om->getVStage1_1Object().size(); i++)


	// 적 & 불렛
	for (int i = 0; i < _stage1_1->getSetEnemyManager()->getVEnemy().size(); i++)
	{
		for (int j = 0; j < _player->getBullet()->getVBullet().size(); j++)
		{
			if (isCollision(_stage1_1->getSetEnemyManager()->getVEnemy()[i]->getEnemyRect(), (*_player->getBullet()->getVBullet()[j]).rc))
			{
				if (_stage1_1->getSetEnemyManager()->getVEnemy()[i]->getEnemyState() != ENEMYSTATE::DEATH)
				{
					MYPOINT tempPo = _stage1_1->getSetEnemyManager()->getVEnemy()[i]->getEnemyPos();
					tempPo.y = _stage1_1->getSetEnemyManager()->getVEnemy()[i]->getEnemyRect().top - 20;
					_itemManager->initCoinItem("coin_item", tempPo, _nowStageName);
					// =========== 맞았을 때 
					_stage1_1->getSetEnemyManager()->getVEnemy()[i]->setHP(_stage1_1->getSetEnemyManager()->getVEnemy()[i]->getHP() - _player->getBullet()->getVBullet()[j]->damage);
					_player->getBullet()->removeBullet(j);
					_stage1_1->getSetEnemyManager()->getVEnemy()[i]->setEnemyState(ENEMYSTATE::HIT);
					// =========== 맞았을 때 

					// =========== 죽을 때 프레임 랜더링

					if (_stage1_1->getSetEnemyManager()->getVEnemy()[i]->getHP() <= 0)
					{
						if (_stage1_1->getSetEnemyManager()->getVEnemy()[i]->getIsLeft())
						{
							_stage1_1->getSetEnemyManager()->getVEnemy()[i]->setFrameX(12);
						}
						else
						{
							_stage1_1->getSetEnemyManager()->getVEnemy()[i]->setFrameX(0);
						}

						_stage1_1->getSetEnemyManager()->getVEnemy()[i]->setEnemyState(ENEMYSTATE::DEATH);
					}




					break;
				}
				// =========== 죽을 때 프레임 랜더링
			}
		}

		for (int k = 0; k < _stage1_1->getSetEnemyManager()->getVEnemy()[i]->getBullet()->getEnemyBullet().size(); k++)
		{
			if (isCollision(_stage1_1->getSetEnemyManager()->getVEnemy()[i]->getBullet()->getEnemyBullet()[k]->rc, (*_player->getPlayerRect())))
			{
				if (!_player->getIsDead())
				{
					_player->setHP(_stage1_1->getSetEnemyManager()->getVEnemy()[i]->getBullet()->getEnemyBullet()[k]->damage);
					_player->setPlayerState(STATE::HIT);
					_stage1_1->getSetEnemyManager()->getVEnemy()[i]->getBullet()->removeEnemuBullet(k);
				}
				break;
			}
		}


	}

	for (int i = 0; i < _itemManager->getVItem().size(); i++)
	{
		if (_itemManager->getVItem()[i]->getType() == ITEM_COIN)
		{
			if (isCollision(_itemManager->getVItem()[i]->getRect(), (*_player->getPlayerRect())))
			{
				_itemManager->removeItemIndex(i);
				SOUNDMANAGER->play("동전", 0.1f);
				_player->setCoin(_player->getCoin() + RND->getFromIntTo(10, 30));
				break;
			}
		}
		else if (_itemManager->getVItem()[i]->getType() == ITEM_HP)
		{

		}
		else if (_itemManager->getVItem()[i]->getType() == ITEM_BULLET)
		{

		}
	}



}

void stageManager::stageShopCollsion()
{
	if (_nowStageName != "STAGE_SHOP") return;

	objectManager* _om = _shop->getObjectManager();
	for (int i = 0; i < _om->getVStageShopObject().size(); i++)
	{

		// --------------------- 박스 충돌 --------------------- //
		if ((_om->getVStageShopObject()[i]->getcanObjectColiision()) == BOX)
		{
			if (isCollisionReaction(_om->getVStageShopObject()[i]->getObjectRect(), *_player->getPlayerRect()))
			{
				_player->refreshCenter();
				break;
			}
		}
		// --------------------- 박스 충돌 --------------------- //

		// --------------------- 텔레포트 충돌 --------------------- //
		if ((_om->getVStageShopObject()[i]->getcanObjectColiision()) == TELEPORT)
		{

			if (isCollision(_om->getVStageShopObject()[i]->getObjectRect(), *_player->getPlayerRect()))
			{
				if (!_eClickAnim->isPlay())
					_eClickAnim->start();

				if (_om->getVStageShopObject()[i]->getTeleportStageNumber() == 1)// _ship 복귀
				{
					if (KEYMANAGER->isOnceKeyDown('E'))
					{
						SCENEMANAGER->changeScene(_typeName[(int)stageType::STAGE_SHIP]);
						_player->spawnPos(_spawnPoint[(int)stageType::STAGE_SHIP]);
						_nowStageName = _typeName[(int)stageType::STAGE_SHIP];

						CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 5500 - WINSIZEX, 2000 - WINSIZEY);
						break;
					}
				}
			}
		}
		// --------------------- 텔레포트 충돌 --------------------- //

	}

	// ============ 아이템 충돌 ============ //
	for (int i = 0; i < _itemManager->getVItem().size(); i++)
	{

		POINT ptPos;
		ptPos.x = _ptMouse.x + CAMERAMANAGER->getL();
		ptPos.y = _ptMouse.y + CAMERAMANAGER->getT();
		if (isPtInRect(_itemManager->getVItem()[i]->getRect(), ptPos))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				if (_itemManager->getVItem()[i]->getType() == ITEM_HP)
				{
				}
				else if (_itemManager->getVItem()[i]->getType() == ITEM_BULLET)
				{

					if (_itemManager->getVItem()[i]->getItemName() == "heavy_bullet_item")
					{
						_player->getWeaponIndex(GUNTYPE::HEAVY)->setPlusCurrentBullet(20);
					}
					else if (_itemManager->getVItem()[i]->getItemName() == "pistol_bullet_item")
					{
						_player->getWeaponIndex(GUNTYPE::PISTOL)->setPlusCurrentBullet(20);
					}
					else
					{
						_player->getWeaponIndex(GUNTYPE::SHOTGUN)->setPlusCurrentBullet(20);
					}

					_itemManager->getVItem()[i]->setIsPlayerGet(true);
				}
			}
		}


		if (isCollision(_itemManager->getVItem()[i]->getRect(), *_player->getPlayerRect()))
		{
			if (!_eClickAnim->isPlay())
				_eClickAnim->start();

			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				if (_itemManager->getVItem()[i]->getType() == ITEM_GUN)
				{
					if (_itemManager->getVItem()[i]->getItemName() == "heavy_gun_item")
					{
						if (_player->getNowWeapoinType() == GUNTYPE::PISTOL)
						{
							_itemManager->initGunItem("pistol_gun_item", _player->getPlayerPos(), "STAGE_SHOP");
						}
						else if (_player->getNowWeapoinType() == GUNTYPE::HEAVY)
						{
							_itemManager->initGunItem("heavy_gun_item", _player->getPlayerPos(), "STAGE_SHOP");
						}
						else
						{
							_itemManager->initGunItem("shotgun_gun_item", _player->getPlayerPos(), "STAGE_SHOP");
						}
						_player->setNowWeaponType(GUNTYPE::HEAVY);
						_itemManager->removeItemIndex(i);
						break;
					}
					else if (_itemManager->getVItem()[i]->getItemName() == "pistol_gun_item")
					{
						if (_player->getNowWeapoinType() == GUNTYPE::PISTOL)
						{
							_itemManager->initGunItem("pistol_gun_item", _player->getPlayerPos(), "STAGE_SHOP");
						}
						else if (_player->getNowWeapoinType() == GUNTYPE::HEAVY)
						{
							_itemManager->initGunItem("heavy_gun_item", _player->getPlayerPos(), "STAGE_SHOP");
						}
						else
						{
							_itemManager->initGunItem("shotgun_gun_item", _player->getPlayerPos(), "STAGE_SHOP");
						}
						_player->setNowWeaponType(GUNTYPE::PISTOL);
						_itemManager->removeItemIndex(i);
						break;
					}
					else
					{
						if (_player->getNowWeapoinType() == GUNTYPE::PISTOL)
						{
							_itemManager->initGunItem("pistol_gun_item", _player->getPlayerPos(), "STAGE_SHOP");
						}
						else if (_player->getNowWeapoinType() == GUNTYPE::HEAVY)
						{
							_itemManager->initGunItem("heavy_gun_item", _player->getPlayerPos(), "STAGE_SHOP");
						}
						else
						{
							_itemManager->initGunItem("shotgun_gun_item", _player->getPlayerPos(), "STAGE_SHOP");
						}
						_player->setNowWeaponType(GUNTYPE::SHOTGUN);
						_itemManager->removeItemIndex(i);
						break;
					}
				}

			}

		}
	}


}

void stageManager::stageBossCollision()
{
	if (_nowStageName != "STAGE_BOSS") return;

	for (int i = 0; i < _player->getBullet()->getVBullet().size(); i++)
	{
		if (isCollision(_player->getBullet()->getVBullet()[i]->rc, _bossStage->getBoss()->getEnemyRect()))
		{
			// -------------------  알 상태 때만 ------------------- //
			if (_bossStage->getBoss()->getEnemyState() == ENEMYSTATE::EGG)
			{
				_bossStage->getBoss()->setEggHP(_bossStage->getBoss()->getEggHP() - 1);
				if (_bossStage->getBoss()->getEggHP() <= 0)
				{
					_bossStage->getBoss()->setEnemyState(ENEMYSTATE::EGGDESTROY);
					_bossStage->getBoss()->setFrameX(0);
				}
			}
			// -------------------  알 상태 때만 ------------------- //

			// -------------------  알 상태 아닐때 ------------------- //
			if (_bossStage->getBoss()->getEnemyState() != ENEMYSTATE::EGG && _bossStage->getBoss()->getEnemyState() != ENEMYSTATE::EGGDESTROY && _bossStage->getBoss()->getEnemyState() != ENEMYSTATE::DEATH)
			{
				_bossStage->getBoss()->setEnemyState(ENEMYSTATE::HIT);
				_bossStage->getBoss()->setHP(_bossStage->getBoss()->getHP() - _player->getBullet()->getVBullet()[i]->damage);

			}
			_player->getBullet()->removeBullet(i);
			break;
			// -------------------  알 상태 아닐때 ------------------- //

		}

	}

	for (int i = 0; i < _bossStage->getBoss()->getBullet()->getBossBullet().size(); i++)
	{
		if (isCollision((*_player->getPlayerRect()), _bossStage->getBoss()->getBullet()->getBossBullet()[i]->rc))
		{
			if (!_player->getIsDead())
			{
				_player->setHP(_bossStage->getBoss()->getBullet()->getBossBullet()[i]->damage);
				_player->setPlayerState(STATE::HIT);
				_bossStage->getBoss()->getBullet()->removeBossBullet(i);
			}
			break;
		}
	}

	for (int i = 0; i < _itemManager->getVItem().size(); i++)
	{
		if (isCollision((*_player->getPlayerRect()), _itemManager->getVItem()[i]->getRect()))
		{
			if (!_eClickAnim->isPlay())
				_eClickAnim->start();

			if (_itemManager->getVItem()[i]->getType() == ITEM_HP)
			{
				if (KEYMANAGER->isOnceKeyDown('E'))
				{
					_player->setHP(-150);
					_itemManager->getVItem()[i]->setIsPlayerGet(true);
					//_itemManager->removeItemIndex(i);
				}
			}
		}
	}



}


