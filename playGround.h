#pragma once
#include "gameNode.h"
#include "player.h"
#include "UIManager.h"
#include "stageManager.h"
#include "intro.h"
enum class PLAYSTATE
{
	GAME_READY,
	GAME_START,
	GAME_OVER,
	END,
};

class playGround : public gameNode
{
private:	

	stageManager*  _stageManager;
	UIManager*     _uiManager;
	player*        _player;
	PLAYSTATE      _nowState;
	char           _buffer[128];
	HFONT          _font, _oldFont;
	
	image*         _intro;
	int            _introCount;
	image*         _loading;
	int            _loadingCount;
	bool           _isStart;
	int            _startCount;
public:
	playGround();
	~playGround();
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
	void imageLoad();                //이미지 불러올 init함수.
	void soundLoad();
public:
	void gameReady();
	void gameStart();
	void gameOver();

	// ---------------------------- 충돌 처리 함수 ---------------------------- //
public:		
	void clipCursor();
	// ---------------------------- 충돌 처리 함수 ---------------------------- //
};

