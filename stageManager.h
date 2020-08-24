#pragma once
#include "gameNode.h"
#include "stage.h"
#include <vector>
#include "stageShip.h"
#include "stageShop.h"
#include "stage1_1.h"
#include "stageBoss.h"
#include "itemManager.h"
#include "intro.h"

class player;        // 상호 참조 전방 선언

class stageManager : public gameNode
{
private:
	string		   _nowStageName; // 현재 스테이지 이름
	string		   _typeName[(int)stageType::END]   = { "STAGE_SHIP", "STAGE_SHOP","STAGE_1_1","STAGE_BOSS" }; // 스테이지 이미지 이름 저장
	MYPOINT		   _spawnPoint[(int)stageType::END] = { {1000,1050},{800,500},{1000,1000},{1000,1000}};				 // 스테이지 시작점
	player*		   _player;      // 상호 참조
	itemManager*   _itemManager;
	stage1_1*	   _stage1_1;
	stageShip*	   _ship;
	stageShop*	   _shop;
	stageBoss*	   _bossStage;
	animation*     _eClickAnim;  // e 클릭하라는 단축키 애니메이션
	bool           _isCreated;
public:
	stageManager() {}
	~stageManager() {}

public:
	HRESULT init();
	void render();
	void update();
	void release();
public:
	void gotoShip();

public:
	void setShip();
	void setShop();									                      // shop 스테이지 설정 함수
	void setEnemyStage();							                      // 1,2  스테이지 설정 함수
	void setBossStage();							                      // boss 스테이지 설정 함수
	string getNowStage() { return _nowStageName; }	                      // 현재 스테이지 getter

public:
	void setPlayerMemoryAddressLink(player* player)  { _player = player; } // 상호 참조 playGround에서 주소 받아오기
public:
	void stageShipCollsion();
	void stage1_1Collsion();
	void stageShopCollsion();
	void stageBossCollision();
};

