#pragma once
#include "stage.h"
#include "boss.h"
class itemManager;
class stageBoss :	public stage
{
private:
	boss* _boss;
	itemManager* _itemManager;
public:
	stageBoss() {}
	~stageBoss() {}
public:
	virtual HRESULT init(string imgName, MYPOINT spawnPoint, itemManager* itemManager);
	virtual void render();
	virtual void update(string nowStageName, MYPOINT playerPos);
	void removeBoss();

public:
	boss* getBoss() { return _boss; }
};

