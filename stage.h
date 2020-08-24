#pragma once
#include "gameNode.h"
enum class stageType
{
	STAGE_SHIP,
	STAGE_SHOP,
	STAGE_1_1,
	STAGE_BOSS,
	END,
};

class stage : public gameNode
{
protected:
	image*     _img;
	string     _imgName;
	MYPOINT    _spawnPoint;
	image*     _animImg;
	animation* _anim;
	string     _animName;
public:
	stage() {}
	~stage() {}

public:
	virtual HRESULT init();
	virtual HRESULT init(string imgName, MYPOINT spawnPoint, string animName);
	virtual void render();
	virtual void update();
	virtual void release();
	image*     getAnimImg() { return _animImg; }
	animation* getAnim() { return _anim; }
};

