#include "stdafx.h"
#include "stageShop.h"
#include "itemManager.h"
HRESULT stageShop::init(string imgName, MYPOINT spawnPoint, itemManager* itemManager)
{
	stage::init(imgName, spawnPoint, "shop_InterUI");
	_om.setStageShop();
	_itemManager = itemManager;
	MYPOINT pos;
	pos.x = 150;
	pos.y = 700;
	_itemManager->initGunItem("heavy_gun_item", pos, "STAGE_SHOP");
	pos.x = 150;
	pos.y = 900;
	_itemManager->initGunItem("shotgun_gun_item", pos, "STAGE_SHOP");
	pos.x = 1000;
	pos.y = 450;
	_itemManager->initBulletItem("heavy_bullet_item", pos, "STAGE_SHOP");
	pos.x = 1080;
	_itemManager->initBulletItem("pistol_bullet_item", pos, "STAGE_SHOP");
	pos.x = 1150;
	_itemManager->initBulletItem("shotgun_bullet_item", pos, "STAGE_SHOP");

	return S_OK;
}

void stageShop::render()
{
	stage::render();
	_om.render();
	_itemManager->render();
}

void stageShop::update()
{
	stage::update();
	_om.update();
	_itemManager->update();
}
