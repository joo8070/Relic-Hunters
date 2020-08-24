#pragma once
#include "item.h"
#include <vector>
class itemManager :	public item
{
private:
	typedef vector<item*> vItem;
	vItem _vItem;

	string _nowStage;

public:
	itemManager() {}
	~itemManager() {}
public:
	HRESULT init();
	void render();
	void update();
	void release();
public:
	void initCoinItem(string imgName, MYPOINT pos, string nowStageName);
	void initGunItem(string imgName, MYPOINT pos, string nowStageName);
	void initHPItem(string imgName, MYPOINT pos, string nowStageName);
	void initBulletItem(string imgName, MYPOINT pos, string nowStageName);
public:

public:
	void removeItemIndex(int arrNum) { _vItem.erase(_vItem.begin() + arrNum); }
	

	vItem getVItem() { return _vItem; }
	void  setNowStageName(string nowStageName) { _nowStage = nowStageName; }
};

