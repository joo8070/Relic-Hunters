#include "stdafx.h"
#include "UIManager.h"
#include "player.h"
#include "stageManager.h"
HRESULT UIManager::init()
{
	_gameoverImg = IMAGEMANAGER->findImage("gameover_UI");
	_gameoverPos.x = CAMERAMANAGER->getX();
	_gameoverPos.y = CAMERAMANAGER->getY();

	_hpImg = IMAGEMANAGER->findImage("HPBARIMG");
	_bulletImg = IMAGEMANAGER->findImage("BULLETIMG");
	return S_OK;
}

void UIManager::render()
{
	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("jimmy_face_UI"), CAMERAMANAGER->getL() + 50, CAMERAMANAGER->getT() + 50);
	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("star_UI"), CAMERAMANAGER->getX() - IMAGEMANAGER->findImage("star_UI")->getWidth() * 0.5f, CAMERAMANAGER->getT() + 50);
	CAMERAMANAGER->render(getMemDC(), _hpImg, CAMERAMANAGER->getL() + 50, CAMERAMANAGER->getT() + 800);
	CAMERAMANAGER->render(getMemDC(), _bulletImg, CAMERAMANAGER->getL() + 50, CAMERAMANAGER->getT() + 700);
	if (_player->getIsDead())
	{
		CAMERAMANAGER->render(getMemDC(), _gameoverImg, _gameoverPos.x , _gameoverPos.y);
	}
}

void UIManager::update()
{
	setGameOver();

}

void UIManager::release()
{
}

void UIManager::setGameOver()
{
	if (_player->getIsDead())
	{	
		_gameoverPos.x = CAMERAMANAGER->getX() - (_gameoverImg->getWidth() * 0.5f);
		_gameoverPos.y = CAMERAMANAGER->getY() - (_gameoverImg->getHeight() * 0.5f);

	}

}
