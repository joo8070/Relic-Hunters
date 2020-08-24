#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "progressBar.h"
enum class ENEMYSTATE
{
	IDLE,
	WALK,
	ATTACK,
	HIT,
	DEATH,
	EGG,
	EGGDESTROY,
};

class enemy : public gameNode
{
protected:
	int			  _hp, _maxHp;		// 적 체력
	float		  _speed;			// 적 스피드
	float		  _angle;			// 적 움직이는 각도
	string        _enemyName;       // 적 이름
	ENEMYSTATE    _state;			// 적 상태
	image*		  _img;				// 적 이미지
	MYPOINT		  _pos;				// 적 위치
	MYRECT		  _rc;				// 적 충돌 렉트
	bool		  _isLeft;			// 적 왼쪽 바라보고 있는지
	int           _frameIndexX;		// 적 프레임 인덱스X
	int           _frameIndexY;		// 적 프레임 인덱스Y
	int           _frameCount;		// 적 프레임 카운트
	int           _thinkCount;		// 적 AI 시간
	bool          _isFollowPlayer; 	// 적 플레이어 따라가는지
	MYPOINT       _rayCast;         // 적 이동 방향에 벽이 있는지
	int           _rayCastLength;   // 적 레이케스트 길이
	bool          _isBlock;         // 벽이 있으면 못옴
	int           _fireCount;       // 
	bullet*       _bullet;          // 총 받아오기
	float         _preMoveX;        // 이전 움직임
	bool          _isDead;          //
	bool          _isFindEffect;    


public:
	virtual HRESULT init(string enemyName, MYPOINT pos);
	virtual void render();
	virtual void update(string nowStageName, MYPOINT playerPos);
	virtual void release();
public:
	virtual void raycast(string nowStageName, MYPOINT playerPos);
	virtual void frameRender();
	
public:
	MYRECT     getEnemyRect() { return _rc; }
	bool       getIsLeft()    { return _isLeft; }
	MYPOINT    getEnemyPos()  { return _pos; }
	void       setEnemyPos(MYPOINT pos) { _pos = pos; }
	void       setEnemyState(ENEMYSTATE state) { _state = state; }
	ENEMYSTATE getEnemyState() { return _state; }
	bullet*    getBullet()    { return _bullet; }
	void       setIsBlock(bool isblock) { _isBlock = isblock; }
	bool       getIsDead() { return _isDead; }
	void       setFrameX(int frameIndexX) { _frameIndexX = frameIndexX; }
	void       setHP(int hp) { _hp = hp; }
	int        getHP() { return _hp; }
};

