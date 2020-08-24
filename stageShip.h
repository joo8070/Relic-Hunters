#pragma once
#include "stage.h"
#include "objectManager.h"
class itemManager;
class stageShip : public stage
{
private:
	objectManager _om;
	itemManager* _itemManager;
public:
	stageShip() {}
	~stageShip() {}

	virtual HRESULT init(string imgName, MYPOINT spawnPoint, itemManager* itemManager);
	virtual void render();
	virtual void update();


	objectManager* getObjectManager() { return &_om; }
};

