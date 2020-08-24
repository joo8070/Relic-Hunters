#pragma once
#include "gameNode.h"

enum OBJECTKIND
{
	BOX,
	DISPLAY,
	TELEPORT,
	COLLAPSE,
	HOLO,
	END
};


class object : public gameNode
{
private:
	image*	   _img;		 // 오브젝트 이미지
	OBJECTKIND _kind;        // 오브젝트 종류
	MYPOINT	   _pos;		 // 오브젝트 위치
	MYRECT	   _rc;	         // 오브젝트 충돌 렉트
	animation* _anim;		 // 오브젝트 애니메이션
	

	int     _teleportStageNum;
	int     _isFrameRender;
	int     _frameCount;
	int     _frameX;
	int     _damage;
	bool    _isTeleportCollision;
	string  _objectName;
	bool    _isRemove;
	bool    _isHide;

public:
	object() {}
	~object() {}
public:
	virtual HRESULT init(MYPOINT pos, const char* objectName, bool isFrameRender, OBJECTKIND kind);

	virtual void render();
	virtual void update();
	virtual void release();

	void setTeleportStageNumber(int num) { _teleportStageNum = num; }
	int  getTeleportStageNumber() { return _teleportStageNum; }
	

	MYRECT getObjectRect() { return _rc; }
	MYPOINT getObjectPosition() { return _pos; }
	void setobjectPosition(MYPOINT pos) { _pos = pos; }
	void setObjectRect(MYRECT rc) { _rc = rc; }
	OBJECTKIND getcanObjectColiision() { return _kind; }
	void setIsTelCollision(bool isCollision) { _isTeleportCollision = isCollision; }
	void setDamage(int damage) { _damage = damage; }
	int  getDamage() { return _damage; }
	bool getIsRemoveObject() { return _isRemove; }
};

