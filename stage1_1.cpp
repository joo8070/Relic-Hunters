#include "stdafx.h"
#include "stage1_1.h"
#include "itemManager.h"
HRESULT stage1_1::init(string imgName, MYPOINT spawnPoint, itemManager* itemManager)
{
	stage::init(imgName, spawnPoint,"1-1_InterUI");

	_om.setStage1_1(); //stage1-1 오브젝트 만들어

	_enemyManager = new enemyManager;
	_enemyManager->init();
	_itemManager = itemManager;

	MYPOINT tempPos[] = { {958,860},{2064,804},{2502,1154},{3160,636},{3370, 1042},{4140 ,1168},{4588, 974},{5008, 1212} };
	for (int i = 0; i < sizeof(tempPos)/sizeof(tempPos[0]); i++)
	{
		_enemyManager->setEnemy(tempPos[i]);
	}

	return S_OK;
}

void stage1_1::render()
{
	stage::render();
	_om.render();
	_itemManager->render();
	_enemyManager->render();
}

void stage1_1::update()
{
	stage::update();
	_om.update();
	_itemManager->update();
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		_enemyManager->release();
	}


}

void stage1_1::release()
{
	_enemyManager->release();
}

void stage1_1::findPlayer(string nowStageName, MYPOINT playerPos)
{
	_enemyManager->update(nowStageName, playerPos);
}
