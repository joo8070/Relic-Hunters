#pragma once
#include "gameNode.h"
#include <vector>

struct tagBullet
{
	const char* imgName;             // 총알 이름
	image*      img;			     // 총알 이미지
	MYPOINT     pos;			     // 총알 위치
	MYPOINT     firePos;		     // 총알 발사 된 위치
	MYRECT      rc;				     // 총알 렉트
	float       speed;			     // 총알 날라가는 스피드
	float       angle;			     // 총알 각도
	int         frameCount;		     // 총알 프레임 카운트
	int         range;			     // 총알 범위
	bool        isFrameRender;       // 프레임 랜더인지
	int         damage;              // 총알 데미지

};

class bullet : public gameNode
{
	vector<tagBullet*>			 _vPlayerBullet;
	vector<tagBullet*>::iterator _viPlayerBullet;

	vector<tagBullet*>            _vEnemyBullet;
	vector<tagBullet*>::iterator  _viEnemyBullet;

	vector<tagBullet*>            _vBossBullet;
	vector<tagBullet*>::iterator  _viBossBullet;

	HBRUSH   _hbrush;
	HBRUSH   _hOldbrush;
	HPEN     _hPen;
	HPEN     _hOldPen;
	COLORREF color;
	int r,g,b;

public:
	bullet() {}
	~bullet() {}
public:
	virtual HRESULT init();
	virtual void render();
	virtual void update(string nowStage);
	virtual void release();
public:
	void playerFire(const char* imgName, int range, bool isFrameRender, MYPOINT pos, float angle, float speed, int damege);
	void enemyFire (const char* imgName, int range, bool isFrameRender, MYPOINT pos, float angle, float speed);
	void setBossBullet(const char* imgName, int range, bool isFrameRender, MYPOINT pos, float angle, float speed);

public:
	void removeBullet(int arrNum);
	void removeEnemuBullet(int arrNum);
	void removeBossBullet(int arrNum);
public:
	vector<tagBullet*> getVBullet()     { return _vPlayerBullet; }
	vector<tagBullet*> getEnemyBullet() { return _vEnemyBullet; }
	vector<tagBullet*> getBossBullet()  { return _vBossBullet; }
};

