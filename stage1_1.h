#pragma once
#include "stage.h"
#include "objectManager.h"
#include "enemyManager.h"

class itemManager;
class stage1_1 : public stage
{
private:
	objectManager _om;
	enemyManager* _enemyManager;
	itemManager* _itemManager;


public:
	stage1_1() {}
	~stage1_1() {}
public:
	virtual HRESULT init(string imgName, MYPOINT spawnPoint, itemManager* itemManager);
	virtual void render();
	virtual void update();
	virtual void release();
	void findPlayer(string nowStageName, MYPOINT playerPos);


	objectManager* getSetObjectManager() { return &_om; }
	enemyManager*  getSetEnemyManager()   { return _enemyManager; }
};

