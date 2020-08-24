#pragma once
#include "gameNode.h"
#include "weapon.h"
#include "bullet.h"
#include "crossHair.h"
#include "progressBar.h"
class stageManager;  // 상호 참조용 전방선언

enum class STATE
{
	IDLE,     
	WALK,     
	RUN,      
	DASH,     
	HIT,      
	HOLO,     
	TELEPORT, 
	DEATH,    
	END,
};

enum CHARACTER
{
	JIMMY,
	PINKY
};

struct tagStaus
{
	int        hp, maxHp;
	float      speed;
};

class player : public gameNode
{
private:
	MYPOINT		 _pos;              // 플레이어 중점
	MYRECT		 _rc;		        // 플레이어 충돌 판정 렉트
	image*		 _img;	            // 플레이어 이미지
	STATE		 _state;            // 플레이어 상태
	tagStaus	 _staus;		    // 플레이어 스텟 변수 구조체
	bool		 _isLeft;           // 플레이어가 마우스 위치에 따라서 어느쪽을 바라보고 있는지
	int			 _frameCount;       // 플레이어 프레임 카운트
	string		 _nowStageName;     // 플레이어 스테이지 현재 위치
	bool		 _isAiming;         // 플레이어 조준 중인지
	GUNTYPE		 _myWeaponType;     // 플레이어가 들고있는 총
	int			 _fireRateCount;    // 플레이어 연사 속도
	int			 _isShot;           // 화면 흔들 때 사용
	int			 _coin;             // 돈
	bool		 _isDead;           // 죽었을 때 
	string		 _name;	            // 캐릭터 변경할 때 필요한 이름
private:
	POINT      _ptPos;              // 마우스 상대값
	// -------------- 픽셀 충돌 변수 -------------- //
	COLORREF color;
	int r, g, b;
	float      _probeYTop, _probeYBottom, _probeXLeft, _probeXRight;
	// -------------- 픽셀 충돌 변수 -------------- //

private:
	// 클래스 참조
	stageManager* _stageManager;              
	weapon*       _weapon[GUNTYPE::END_GUN];  
	bullet*       _bullet;
	crossHair*    _crossHair;
public:
	player() {}
	~player() {}

public:
	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

public:
	void setStageManagerMemoryAddressLink(stageManager* sm) { _stageManager = sm; } // 상호 참조 playGround에서 주소 받아오기

public:
	void statusInit(CHARACTER charName); // 플레이어 스텟 초기화
	void move();						 // 플레이어 이동 컨트롤 함수
	void spawnPos(MYPOINT pos);			 // 플레이어 워프시 이동 시키는 함수
	void collision();                    // 플레이어 충돌
	void playerFrameRender();            // 플레이어 상태 프레임 랜더 함수
	void refreshCenter();                // 플레이어 렉트 중앙 설정
	void gunSetting();                   // 플레이어 총 셋팅
	void gunControl();                   // 플레이어 총 컨트롤

public:
	void     setPlayerPos(MYPOINT pos) { _pos = pos; }		 // 플레이어 위치 setter
	MYPOINT  getPlayerPos()    { return _pos; }				 // 플레이어 위치 getter
	bool     getPlayerIsLeft() { return _isLeft; }			 // 플레이어 바라보는 방향 getter   
	MYRECT*  getPlayerRect()   { return &_rc; }				 // 플레이어 렉트 getter
	string   getNowStageName() { return _nowStageName; }	 // 플레이어 현재 스테이지
	bullet*  getBullet()       { return _bullet; }			 // 플레이어 총알 받아오기
	void     setPlayerState(STATE state) { _state = state; } // 플레이어 상태 setter
	void     setCoin(int coin) { _coin = coin; }
	int      getCoin() { return _coin; }
	weapon*  getNowWeapon() { return  _weapon[_myWeaponType]; }
	int      getHP() { return _staus.hp; }
	void     setHP(int damage) { _staus.hp = _staus.hp - damage; }
	bool     getIsDead() { return _isDead; }
	void     setIsDead(bool isdead) { _isDead = isdead; }
	weapon*  getWeaponIndex(GUNTYPE index) { return _weapon[index]; }
	void     setNowWeaponType(GUNTYPE type) { _myWeaponType = type; }
	GUNTYPE  getNowWeapoinType() { return _myWeaponType; }
	string   getCharName() { return _name; }
	void     setCharName(string name) { _name = name; }
	int      getMaxHP() { return _staus.maxHp; }
};

