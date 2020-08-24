#pragma once
#include "gameNode.h"
#include "enemy.h"
#include "gruntEnemy.h"
#include <vector>

class enemyManager : public gameNode
{
private:
	vector<enemy*>           _vEnemy;
	vector<enemy*>::iterator _viEnemy;
	string _enemyName[6] = { {"tutle1"},{"duck1"},{"tutle2"},{"duck2"},{"tutle3"},{"duck3"} };
public:
	HRESULT init();
	void render();
	void update(string nowStageName, MYPOINT playerPosion);
	void release();

public:
	void setEnemy(MYPOINT pos);
	void removeEnemy(int arrNum);
	vector<enemy*> getVEnemy() { return _vEnemy; }
};

