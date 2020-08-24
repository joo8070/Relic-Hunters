#pragma once
#include "stage.h"
#include "objectManager.h"
class itemManager;
class stageShop : public stage
{
private:
	objectManager _om;
	itemManager* _itemManager;
public:
	stageShop() {}
	~stageShop() {}

	virtual HRESULT init(string imgName, MYPOINT spawnPoint, itemManager* itemManager);
	virtual void render();
	virtual void update();


	objectManager* getObjectManager() { return &_om; }
};

