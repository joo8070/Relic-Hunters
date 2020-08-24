#pragma once
#include "enemy.h"
class gruntEnemy :	public enemy
{
	progressBar*  _progressBar;		// Àû hp¹Ù

public:
	gruntEnemy() {}
	~gruntEnemy() {}
	virtual HRESULT init(string enemyName, MYPOINT pos);
	virtual void render();
	virtual void update(string nowStageName, MYPOINT playerPos);
	virtual void release();

	void findPlayer(string nowStageName, MYPOINT playerPos);
	void fire(MYPOINT pos);
};

