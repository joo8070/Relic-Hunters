#include "stdafx.h"
#include "stageShip.h"
#include "itemManager.h"
HRESULT stageShip::init(string imgName, MYPOINT spawnPoint, itemManager* itemManager)
{
	stage::init(imgName, spawnPoint,"");
	_om.setStageShip();
	_itemManager = itemManager;


	return S_OK;
}

void stageShip::render()
{
	stage::render();
	_om.render();
	_itemManager->render();
}

void stageShip::update()
{
	stage::update();
	_om.update();
	_itemManager->update();


	//if (KEYMANAGER->isOnceKeyDown('N'))
	//{
	//	MYPOINT pos;
	//	pos.x = 1000;
	//	pos.y = 1000;
	//	_itemManager->initCoinItem("coin_item", pos);
	//}

}

