#pragma once
#include "gameNode.h"

enum ITEMTYPE
{
	ITEM_GUN,
	ITEM_COIN,
	ITEM_HP,
	ITEM_BULLET,
	ITEM_RELIC,
};

class item : public gameNode
{
protected:
	string     _imgName;
	string     _stageName;
	bool       _isFrameImg;
	MYPOINT    _pos;
	MYPOINT    _dropStartPos;
	MYRECT     _rc;
	ITEMTYPE   _type;
	float      _angle;
	float      _gravity;
	int        _frameX;
	bool       _isDisappear;
	bool       _isPlayerGet;
	int        _count;
public:
	item() {}
	~item() {}
public:
	virtual HRESULT init(string imgName, MYPOINT pos, ITEMTYPE type, string nowStageName);
	virtual void render();
	virtual void update();
	virtual void release();
public:
	void updateCoinItem();
	void updateHPItem();
	void updateBulletItem();
public:
	int      getFrameX() { return _frameX; }
	ITEMTYPE getType() { return _type; }
	MYRECT   getRect() { return _rc; }
	string   getStageName() { return _stageName; }
	bool     getIsDisappear() { return _isDisappear; }
	void     setIsPlayerGet(bool isGet) { _isPlayerGet = isGet; }
	string   getItemName() { return _imgName; }
};

