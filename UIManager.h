#pragma once
#include "gameNode.h"

class player;
class stageManager;
class UIManager : public gameNode
{
private:
	image*        _hpImg;
	image*        _bulletImg;
private:
	image*        _gameoverImg;
	MYPOINT       _gameoverPos;
	int           _gameoverCount;
private:

	player*       _player;
	stageManager* _stageManager;

public:
	UIManager() {}
	~UIManager() {}

	HRESULT init();
	void render();
	void update();
	void release();

	void setStageManagerMemoryAddressLink(stageManager* stageManager) { _stageManager = stageManager; }
	void setPlayerMemoryAddressLink(player* player) { _player = player; }

	void setGameOver();

};

