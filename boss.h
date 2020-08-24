#pragma once
#include "enemy.h"

enum BOSSPATTERN
{
	ATTACK1,		// 기본 공격
	ATTACK2,
	ATTACK3,
	ATTACK4,
};

class boss : public enemy
{
private:
	int			_eggHP;
	image*		_gunImg;
	int         _patternChangeTime;
	BOSSPATTERN _pattern;
	progressBar*  _progressBar;		// 적 hp바

public:
	virtual HRESULT init(string enemyName, MYPOINT pos);
	virtual void render();
	virtual void update(string nowStageName, MYPOINT playerPos);
	virtual void release();
public:
	void attack1(MYPOINT playerPos);
	void attack2(MYPOINT playerPos);
	void attack3(MYPOINT playerPos);
	void findPlayer(MYPOINT playerPos);
	void patternChange();
public:
	void setEggHP(int eggHP) { _eggHP = eggHP; }
	int  getEggHP() { return _eggHP; }
};

