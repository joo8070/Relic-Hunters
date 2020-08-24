#include "stdafx.h"
#include "stageBoss.h"
#include "enemyManager.h"
#include "itemManager.h"
HRESULT stageBoss::init(string imgName, MYPOINT spawnPoint, itemManager* itemManager)
{
	stage::init(imgName, spawnPoint, "boss_InterUI");
	_boss = new boss;
	MYPOINT temp;
	temp.x = 2000;
	temp.y = 1500;
	_boss->init("boss", temp);

	_itemManager = itemManager;
	temp.x = 800;
	temp.y = 1500;
	_itemManager->initHPItem("health_item", temp, "STAGE_BOSS");


	temp.x = 880;
	temp.y = 1200;
	_itemManager->initHPItem("health_item", temp, "STAGE_BOSS");

	return S_OK;
}

void stageBoss::render()
{
	stage::render();
	_boss->render();
	_itemManager->render();
	
}

void stageBoss::update(string nowStageName, MYPOINT playerPos)
{
	stage::update();
	_boss->update(nowStageName, playerPos);

	_itemManager->update();
}

void stageBoss::removeBoss()
{
	delete _boss;
}



