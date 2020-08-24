#pragma once
#include "gameNode.h"

enum GUNTYPE
{
	PISTOL,
	SHOTGUN,
	HEAVY,
	END_GUN
};

class weapon : public gameNode
{
protected:
	image*  _img;				  // 총 이미지
	MYPOINT _pos;				  // 총 위치
	int     _fireRate;			  // 총 연사 속도
	int     _reloadTime;          // 장전 속도
	int	    _carryBulletCount;    // 들고 다니는 총알 갯수
	int	    _currentBulletCount;  // 현재 총알 갯수
	int	    _maxBulletCount;      // 총알 최대 가질 수 있는 갯수
	int	    _reloadBulletCount;   // 장전 시 장전되는 총알 갯수	
	bool    _isReload;
public:
	weapon() {}
	~weapon() {}
public:
	virtual HRESULT init(GUNTYPE type);
	virtual void update(bool isLeft, MYPOINT pos, GUNTYPE type);
	virtual void render();
	virtual void release();

public:
	void reload();

public:
	void setPistol();
	void setShotgun();
	void setHeavy();

public:
	image* getImage()	  { return _img; }
	int  getFireRate()    { return _fireRate; }
	int  getCarryBullet() { return _carryBulletCount; }
	int  getCurrentBullet() { return _currentBulletCount; }
	void setCarryBullet(int carryBullet) { _carryBulletCount = carryBullet; }
	bool getIsReload() { return _isReload; }
	void setPlusCurrentBullet(int getBullet) { _currentBulletCount += getBullet; }
};

